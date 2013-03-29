--- a/net/bluetooth/hidp/core.c
+++ b/net/bluetooth/hidp/core.c
@@ -383,6 +383,7 @@
 	return ret;
 }
 
+#if defined(CONFIG_COMPAT_BT_SOCK_CREATE_NEEDS_KERN)
 static int hidp_output_raw_report(struct hid_device *hid, unsigned char *data, size_t count,
 		unsigned char report_type)
 {
@@ -441,6 +442,16 @@
 	mutex_unlock(&session->report_mutex);
 	return ret;
 }
+#elif (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,27))
+static int hidp_output_raw_report(struct hid_device *hid, unsigned char *data, size_t count)
+{
+	if (hidp_send_ctrl_message(hid->driver_data,
+			HIDP_TRANS_SET_REPORT | HIDP_DATA_RTYPE_FEATURE,
+			data, count))
+		return -ENOMEM;
+	return count;
+}
+#endif
 
 static void hidp_idle_timeout(unsigned long arg)
 {
@@ -743,8 +754,14 @@
 	}
 
 	if (session->hid) {
+#if (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,27))
 		hid_destroy_device(session->hid);
 		session->hid = NULL;
+#else
+		if (session->hid->claimed & HID_CLAIMED_INPUT)
+			hidinput_disconnect(session->hid);
+		hid_free_device(session->hid);
+#endif
 	}
 
 	/* Wakeup user-space polling for socket errors */
@@ -855,6 +872,70 @@
 {
 }
 
+#if (LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,27))
+static const struct {
+	__u16 idVendor;
+	__u16 idProduct;
+	unsigned quirks;
+} hidp_blacklist[] = {
+	/* Apple wireless Mighty Mouse */
+	{ 0x05ac, 0x030c, HID_QUIRK_MIGHTYMOUSE | HID_QUIRK_INVERT_HWHEEL },
+
+	{ }	/* Terminating entry */
+};
+static void hidp_setup_quirks(struct hid_device *hid)
+{
+	unsigned int n;
+
+	for (n = 0; hidp_blacklist[n].idVendor; n++)
+		if (hidp_blacklist[n].idVendor == le16_to_cpu(hid->vendor) &&
+				hidp_blacklist[n].idProduct == le16_to_cpu(hid->product))
+			hid->quirks = hidp_blacklist[n].quirks;
+}
+
+static void hidp_setup_hid(struct hidp_session *session,
+				struct hidp_connadd_req *req)
+{
+	struct hid_device *hid = session->hid;
+	struct hid_report *report;
+	bdaddr_t src, dst;
+
+	session->hid = hid;
+
+	hid->driver_data = session;
+
+	baswap(&src, &bt_sk(session->ctrl_sock->sk)->src);
+	baswap(&dst, &bt_sk(session->ctrl_sock->sk)->dst);
+
+	hid->bus     = BUS_BLUETOOTH;
+	hid->vendor  = req->vendor;
+	hid->product = req->product;
+	hid->version = req->version;
+	hid->country = req->country;
+
+	strncpy(hid->name, req->name, 128);
+	strncpy(hid->phys, batostr(&src), 64);
+	strncpy(hid->uniq, batostr(&dst), 64);
+
+	hid->dev = hidp_get_device(session);
+	hid->hid_open  = hidp_open;
+	hid->hid_close = hidp_close;
+
+	hid->hidinput_input_event = hidp_hidinput_event;
+
+	hidp_setup_quirks(hid);
+
+	list_for_each_entry(report, &hid->report_enum[HID_INPUT_REPORT].report_list, list)
+		hidp_send_report(session, report);
+
+	list_for_each_entry(report, &hid->report_enum[HID_FEATURE_REPORT].report_list, list)
+		hidp_send_report(session, report);
+
+	if (hidinput_connect(hid) == 0)
+		hid->claimed |= HID_CLAIMED_INPUT;
+}
+#else
+
 static int hidp_parse(struct hid_device *hid)
 {
 	struct hidp_session *session = hid->driver_data;
@@ -946,7 +1027,9 @@
 	hid->dev.parent = &session->conn->dev;
 	hid->ll_driver = &hidp_hid_driver;
 
+#if (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,38))
 	hid->hid_get_raw_report = hidp_get_raw_report;
+#endif
 	hid->hid_output_raw_report = hidp_output_raw_report;
 
 	/* True if device is blacklisted in drivers/hid/hid-core.c */
@@ -964,6 +1047,7 @@
 
 	return err;
 }
+#endif
 
 int hidp_add_connection(struct hidp_connadd_req *req, struct socket *ctrl_sock, struct socket *intr_sock)
 {
@@ -979,6 +1063,39 @@
 
 	BT_DBG("rd_data %p rd_size %d", req->rd_data, req->rd_size);
 
+#if (LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,27))
+	if (req->rd_size > 0) {
+		unsigned char *buf = kmalloc(req->rd_size, GFP_KERNEL);
+
+		if (!buf) {
+			kfree(session);
+			return -ENOMEM;
+		}
+
+		if (copy_from_user(buf, req->rd_data, req->rd_size)) {
+			kfree(buf);
+			kfree(session);
+			return -EFAULT;
+		}
+
+		session->hid = hid_parse_report(buf, req->rd_size);
+
+		kfree(buf);
+
+		if (!session->hid) {
+			kfree(session);
+			return -EINVAL;
+		}
+	}
+
+	if (!session->hid) {
+		session->input = input_allocate_device();
+		if (!session->input) {
+			kfree(session);
+			return -ENOMEM;
+		}
+	}
+#endif
 	down_write(&hidp_session_sem);
 
 	s = __hidp_get_session(&bt_sk(ctrl_sock->sk)->dst);
@@ -1026,6 +1143,7 @@
 
 	__hidp_link_session(session);
 
+#if (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,27))
 	if (req->rd_size > 0) {
 		err = hidp_setup_hid(session, req);
 		if (err && err != -ENODEV)
@@ -1037,6 +1155,16 @@
 		if (err < 0)
 			goto purge;
 	}
+#else
+	if (session->input) {
+		err = hidp_setup_input(session, req);
+		if (err < 0)
+			goto failed;
+	}
+
+	if (session->hid)
+		hidp_setup_hid(session, req);
+#endif
 
 	hidp_set_timer(session);
 
@@ -1095,6 +1223,7 @@
 		session->input = NULL;
 	}
 
+#if (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,27))
 	if (session->hid) {
 		hid_destroy_device(session->hid);
 		session->hid = NULL;
@@ -1108,10 +1237,15 @@
 
 	skb_queue_purge(&session->ctrl_transmit);
 	skb_queue_purge(&session->intr_transmit);
+#endif
 
 failed:
 	up_write(&hidp_session_sem);
 
+#if (LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,27))
+	if (session->hid)
+		hid_free_device(session->hid);
+#endif
 	kfree(session);
 	return err;
 }
