--- a/drivers/net/usb/rndis_host.c
+++ b/drivers/net/usb/rndis_host.c
@@ -332,6 +332,11 @@
 	u.init->major_version = cpu_to_le32(1);
 	u.init->minor_version = cpu_to_le32(0);
 
+#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,29))
+	/* can't we remove this? */
+	net->change_mtu = NULL;
+#endif
+
 	/* max transfer (in spec) is 0x4000 at full speed, but for
 	 * TX we'll stick to one Ethernet packet plus RNDIS framing.
 	 * For RX we handle drivers that zero-pad to end-of-packet.
