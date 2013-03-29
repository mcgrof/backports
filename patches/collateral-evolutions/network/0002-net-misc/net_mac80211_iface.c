--- a/net/mac80211/iface.c
+++ b/net/mac80211/iface.c
@@ -1018,6 +1018,11 @@
 	ether_setup(dev);
 	dev->priv_flags &= ~IFF_TX_SKB_SHARING;
 	netdev_attach_ops(dev, &ieee80211_dataif_ops);
+#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,29))
+	/* Do we need this ? */
+	/* we will validate the address ourselves in ->open */
+	dev->validate_addr = NULL;
+#endif
 	dev->destructor = free_netdev;
 }
 
