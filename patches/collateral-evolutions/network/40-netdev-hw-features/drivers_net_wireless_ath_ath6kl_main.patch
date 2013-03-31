--- a/drivers/net/wireless/ath/ath6kl/main.c
+++ b/drivers/net/wireless/ath/ath6kl/main.c
@@ -1116,6 +1116,7 @@
 	return &vif->net_stats;
 }
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39))
 static int ath6kl_set_features(struct net_device *dev,
 			       netdev_features_t features)
 {
@@ -1148,6 +1149,7 @@
 
 	return err;
 }
+#endif
 
 static void ath6kl_set_multicast_list(struct net_device *ndev)
 {
@@ -1295,7 +1297,9 @@
 	.ndo_stop               = ath6kl_close,
 	.ndo_start_xmit         = ath6kl_data_tx,
 	.ndo_get_stats          = ath6kl_get_stats,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39))
 	.ndo_set_features       = ath6kl_set_features,
+#endif
 	.ndo_set_rx_mode	= ath6kl_set_multicast_list,
 };
 
@@ -1312,7 +1316,11 @@
 					WMI_MAX_TX_META_SZ +
 					ATH6KL_HTC_ALIGN_BYTES, 4);
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39))
 	dev->hw_features |= NETIF_F_IP_CSUM | NETIF_F_RXCSUM;
+#else
+	dev->features |= NETIF_F_IP_CSUM;
+#endif
 
 	return;
 }
