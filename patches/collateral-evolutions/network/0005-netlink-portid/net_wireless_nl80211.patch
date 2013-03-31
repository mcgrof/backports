--- a/net/wireless/nl80211.c
+++ b/net/wireless/nl80211.c
@@ -1593,7 +1593,7 @@
 		/* attempt to fit multiple wiphy data chunks into the skb */
 		do {
 			ret = nl80211_send_wiphy(dev, skb,
-						 NETLINK_CB(cb->skb).portid,
+						 NETLINK_CB_PORTID(cb->skb),
 						 cb->nlh->nlmsg_seq,
 						 NLM_F_MULTI,
 						 split, &cb->args[1],
@@ -1642,7 +1642,7 @@
 	if (!msg)
 		return -ENOMEM;
 
-	if (nl80211_send_wiphy(dev, msg, info->snd_portid, info->snd_seq, 0,
+	if (nl80211_send_wiphy(dev, msg, genl_info_snd_portid(info), info->snd_seq, 0,
 			       false, NULL, NULL, NULL) < 0) {
 		nlmsg_free(msg);
 		return -ENOBUFS;
@@ -2222,7 +2222,7 @@
 				if_idx++;
 				continue;
 			}
-			if (nl80211_send_iface(skb, NETLINK_CB(cb->skb).portid,
+			if (nl80211_send_iface(skb, NETLINK_CB_PORTID(cb->skb),
 					       cb->nlh->nlmsg_seq, NLM_F_MULTI,
 					       rdev, wdev) < 0) {
 				mutex_unlock(&rdev->devlist_mtx);
@@ -2253,7 +2253,7 @@
 	if (!msg)
 		return -ENOMEM;
 
-	if (nl80211_send_iface(msg, info->snd_portid, info->snd_seq, 0,
+	if (nl80211_send_iface(msg, genl_info_snd_portid(info), info->snd_seq, 0,
 			       dev, wdev) < 0) {
 		nlmsg_free(msg);
 		return -ENOBUFS;
@@ -2478,7 +2478,7 @@
 		break;
 	}
 
-	if (nl80211_send_iface(msg, info->snd_portid, info->snd_seq, 0,
+	if (nl80211_send_iface(msg, genl_info_snd_portid(info), info->snd_seq, 0,
 			       rdev, wdev) < 0) {
 		nlmsg_free(msg);
 		return -ENOBUFS;
@@ -2613,7 +2613,7 @@
 	if (!msg)
 		return -ENOMEM;
 
-	hdr = nl80211hdr_put(msg, info->snd_portid, info->snd_seq, 0,
+	hdr = nl80211hdr_put(msg, genl_info_snd_portid(info), info->snd_seq, 0,
 			     NL80211_CMD_NEW_KEY);
 	if (IS_ERR(hdr))
 		return PTR_ERR(hdr);
@@ -3549,7 +3549,7 @@
 			goto out_err;
 
 		if (nl80211_send_station(skb,
-				NETLINK_CB(cb->skb).portid,
+				NETLINK_CB_PORTID(cb->skb),
 				cb->nlh->nlmsg_seq, NLM_F_MULTI,
 				dev, netdev, mac_addr,
 				&sinfo) < 0)
@@ -3595,7 +3595,7 @@
 	if (!msg)
 		return -ENOMEM;
 
-	if (nl80211_send_station(msg, info->snd_portid, info->snd_seq, 0,
+	if (nl80211_send_station(msg, genl_info_snd_portid(info), info->snd_seq, 0,
 				 rdev, dev, mac_addr, &sinfo) < 0) {
 		nlmsg_free(msg);
 		return -ENOBUFS;
@@ -4195,7 +4195,7 @@
 		if (err)
 			goto out_err;
 
-		if (nl80211_send_mpath(skb, NETLINK_CB(cb->skb).portid,
+		if (nl80211_send_mpath(skb, NETLINK_CB_PORTID(cb->skb),
 				       cb->nlh->nlmsg_seq, NLM_F_MULTI,
 				       netdev, dst, next_hop,
 				       &pinfo) < 0)
@@ -4244,7 +4244,7 @@
 	if (!msg)
 		return -ENOMEM;
 
-	if (nl80211_send_mpath(msg, info->snd_portid, info->snd_seq, 0,
+	if (nl80211_send_mpath(msg, genl_info_snd_portid(info), info->snd_seq, 0,
 				 dev, dst, next_hop, &pinfo) < 0) {
 		nlmsg_free(msg);
 		return -ENOBUFS;
@@ -4508,7 +4508,7 @@
 	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
 	if (!msg)
 		return -ENOMEM;
-	hdr = nl80211hdr_put(msg, info->snd_portid, info->snd_seq, 0,
+	hdr = nl80211hdr_put(msg, genl_info_snd_portid(info), info->snd_seq, 0,
 			     NL80211_CMD_GET_MESH_CONFIG);
 	if (!hdr)
 		goto out;
@@ -4858,7 +4858,7 @@
 		goto out;
 	}
 
-	hdr = nl80211hdr_put(msg, info->snd_portid, info->snd_seq, 0,
+	hdr = nl80211hdr_put(msg, genl_info_snd_portid(info), info->snd_seq, 0,
 			     NL80211_CMD_GET_REG);
 	if (!hdr)
 		goto put_failure;
@@ -5558,7 +5558,7 @@
 
 	ASSERT_WDEV_LOCK(wdev);
 
-	hdr = nl80211hdr_put(msg, NETLINK_CB(cb->skb).portid, seq, flags,
+	hdr = nl80211hdr_put(msg, NETLINK_CB_PORTID(cb->skb), seq, flags,
 			     NL80211_CMD_NEW_SCAN_RESULTS);
 	if (!hdr)
 		return -1;
@@ -5789,7 +5789,7 @@
 		}
 
 		if (nl80211_send_survey(skb,
-				NETLINK_CB(cb->skb).portid,
+				NETLINK_CB_PORTID(cb->skb),
 				cb->nlh->nlmsg_seq, NLM_F_MULTI,
 				netdev,
 				&survey) < 0)
@@ -6448,7 +6448,7 @@
 	}
 
 	while (1) {
-		void *hdr = nl80211hdr_put(skb, NETLINK_CB(cb->skb).portid,
+		void *hdr = nl80211hdr_put(skb, NETLINK_CB_PORTID(cb->skb),
 					   cb->nlh->nlmsg_seq, NLM_F_MULTI,
 					   NL80211_CMD_TESTMODE);
 		struct nlattr *tmdata;
@@ -6527,7 +6527,7 @@
 		return NULL;
 
 	return __cfg80211_testmode_alloc_skb(rdev, approxlen,
-				rdev->testmode_info->snd_portid,
+				genl_info_snd_portid(rdev->testmode_info),
 				rdev->testmode_info->snd_seq,
 				GFP_KERNEL);
 }
@@ -6887,7 +6887,7 @@
 	if (!msg)
 		return -ENOMEM;
 
-	hdr = nl80211hdr_put(msg, info->snd_portid, info->snd_seq, 0,
+	hdr = nl80211hdr_put(msg, genl_info_snd_portid(info), info->snd_seq, 0,
 			     NL80211_CMD_REMAIN_ON_CHANNEL);
 
 	if (IS_ERR(hdr)) {
@@ -7106,7 +7106,7 @@
 	if (!rdev->ops->mgmt_tx)
 		return -EOPNOTSUPP;
 
-	return cfg80211_mlme_register_mgmt(wdev, info->snd_portid, frame_type,
+	return cfg80211_mlme_register_mgmt(wdev, genl_info_snd_portid(info), frame_type,
 			nla_data(info->attrs[NL80211_ATTR_FRAME_MATCH]),
 			nla_len(info->attrs[NL80211_ATTR_FRAME_MATCH]));
 }
@@ -7176,7 +7176,7 @@
 		if (!msg)
 			return -ENOMEM;
 
-		hdr = nl80211hdr_put(msg, info->snd_portid, info->snd_seq, 0,
+		hdr = nl80211hdr_put(msg, genl_info_snd_portid(info), info->snd_seq, 0,
 				     NL80211_CMD_FRAME);
 
 		if (IS_ERR(hdr)) {
@@ -7291,7 +7291,7 @@
 	if (!msg)
 		return -ENOMEM;
 
-	hdr = nl80211hdr_put(msg, info->snd_portid, info->snd_seq, 0,
+	hdr = nl80211hdr_put(msg, genl_info_snd_portid(info), info->snd_seq, 0,
 			     NL80211_CMD_GET_POWER_SAVE);
 	if (!hdr) {
 		err = -ENOBUFS;
@@ -7583,7 +7583,7 @@
 	if (!msg)
 		return -ENOMEM;
 
-	hdr = nl80211hdr_put(msg, info->snd_portid, info->snd_seq, 0,
+	hdr = nl80211hdr_put(msg, genl_info_snd_portid(info), info->snd_seq, 0,
 			     NL80211_CMD_GET_WOWLAN);
 	if (!hdr)
 		goto nla_put_failure;
@@ -8007,7 +8007,7 @@
 	if (wdev->ap_unexpected_nlportid)
 		return -EBUSY;
 
-	wdev->ap_unexpected_nlportid = info->snd_portid;
+	wdev->ap_unexpected_nlportid = genl_info_snd_portid(info);
 	return 0;
 }
 
@@ -8037,7 +8037,7 @@
 	if (!msg)
 		return -ENOMEM;
 
-	hdr = nl80211hdr_put(msg, info->snd_portid, info->snd_seq, 0,
+	hdr = nl80211hdr_put(msg, genl_info_snd_portid(info), info->snd_seq, 0,
 			     NL80211_CMD_PROBE_CLIENT);
 
 	if (IS_ERR(hdr)) {
@@ -8081,13 +8081,13 @@
 	/* First, check if already registered. */
 	spin_lock_bh(&rdev->beacon_registrations_lock);
 	list_for_each_entry(reg, &rdev->beacon_registrations, list) {
-		if (reg->nlportid == info->snd_portid) {
+		if (reg->nlportid == genl_info_snd_portid(info)) {
 			rv = -EALREADY;
 			goto out_err;
 		}
 	}
 	/* Add it to the list */
-	nreg->nlportid = info->snd_portid;
+	nreg->nlportid = genl_info_snd_portid(info);
 	list_add(&nreg->list, &rdev->beacon_registrations);
 
 	spin_unlock_bh(&rdev->beacon_registrations_lock);
@@ -8160,7 +8160,7 @@
 	if (!msg)
 		return -ENOMEM;
 
-	hdr = nl80211hdr_put(msg, info->snd_portid, info->snd_seq, 0,
+	hdr = nl80211hdr_put(msg, genl_info_snd_portid(info), info->snd_seq, 0,
 			     NL80211_CMD_GET_PROTOCOL_FEATURES);
 	if (!hdr)
 		goto nla_put_failure;
@@ -10565,12 +10565,12 @@
 
 	list_for_each_entry_rcu(rdev, &cfg80211_rdev_list, list) {
 		list_for_each_entry_rcu(wdev, &rdev->wdev_list, list)
-			cfg80211_mlme_unregister_socket(wdev, notify->portid);
+			cfg80211_mlme_unregister_socket(wdev, netlink_notify_portid(notify));
 
 		spin_lock_bh(&rdev->beacon_registrations_lock);
 		list_for_each_entry_safe(reg, tmp, &rdev->beacon_registrations,
 					 list) {
-			if (reg->nlportid == notify->portid) {
+			if (reg->nlportid == netlink_notify_portid(notify)) {
 				list_del(&reg->list);
 				kfree(reg);
 				break;
