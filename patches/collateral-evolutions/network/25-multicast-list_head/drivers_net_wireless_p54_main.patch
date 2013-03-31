--- a/drivers/net/wireless/p54/main.c
+++ b/drivers/net/wireless/p54/main.c
@@ -364,11 +364,18 @@
 	return ret;
 }
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 static u64 p54_prepare_multicast(struct ieee80211_hw *dev,
 				 struct netdev_hw_addr_list *mc_list)
+#else
+static u64 p54_prepare_multicast(struct ieee80211_hw *dev, int mc_count,
+				 struct dev_addr_list *ha)
+#endif
 {
 	struct p54_common *priv = dev->priv;
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 	struct netdev_hw_addr *ha;
+#endif
 	int i;
 
 	BUILD_BUG_ON(ARRAY_SIZE(priv->mc_maclist) !=
@@ -378,12 +385,23 @@
 	 * Otherwise the firmware will drop it and ARP will no longer work.
 	 */
 	i = 1;
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 	priv->mc_maclist_num = netdev_hw_addr_list_count(mc_list) + i;
 	netdev_hw_addr_list_for_each(ha, mc_list) {
 		memcpy(&priv->mc_maclist[i], ha->addr, ETH_ALEN);
+#else
+	priv->mc_maclist_num = mc_count + i;
+	while (i <= mc_count) {
+		if (!ha)
+			break;
+		memcpy(&priv->mc_maclist[i], ha->dmi_addr, ETH_ALEN);
+#endif
 		i++;
 		if (i >= ARRAY_SIZE(priv->mc_maclist))
 			break;
+#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,35))
+		ha = ha->next;
+#endif
 	}
 
 	return 1; /* update */
