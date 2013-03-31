--- a/net/mac80211/iface.c
+++ b/net/mac80211/iface.c
@@ -1518,6 +1518,7 @@
 			return -ENOMEM;
 		dev_net_set(ndev, wiphy_net(local->hw.wiphy));
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,26))
 		ndev->needed_headroom = local->tx_headroom +
 					4*6 /* four MAC addresses */
 					+ 2 + 2 + 2 + 2 /* ctl, dur, seq, qos */
@@ -1526,6 +1527,7 @@
 					- ETH_HLEN /* ethernet hard_header_len */
 					+ IEEE80211_ENCRYPT_HEADROOM;
 		ndev->needed_tailroom = IEEE80211_ENCRYPT_TAILROOM;
+#endif
 
 		ret = dev_alloc_name(ndev, ndev->name);
 		if (ret < 0) {
