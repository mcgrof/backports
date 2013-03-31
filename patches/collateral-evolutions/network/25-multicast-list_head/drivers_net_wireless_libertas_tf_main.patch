--- a/drivers/net/wireless/libertas_tf/main.c
+++ b/drivers/net/wireless/libertas_tf/main.c
@@ -421,20 +421,36 @@
 }
 
 static u64 lbtf_op_prepare_multicast(struct ieee80211_hw *hw,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 				     struct netdev_hw_addr_list *mc_list)
+#else
+				     int mc_count, struct dev_addr_list *ha)
+#endif
 {
 	struct lbtf_private *priv = hw->priv;
 	int i;
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 	struct netdev_hw_addr *ha;
 	int mc_count = netdev_hw_addr_list_count(mc_list);
+#endif
 
 	if (!mc_count || mc_count > MRVDRV_MAX_MULTICAST_LIST_SIZE)
 		return mc_count;
 
 	priv->nr_of_multicastmacaddr = mc_count;
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 	i = 0;
 	netdev_hw_addr_list_for_each(ha, mc_list)
 		memcpy(&priv->multicastlist[i++], ha->addr, ETH_ALEN);
+#else
+	for (i = 0; i < mc_count; i++) {
+		if (!ha)
+			break;
+		memcpy(&priv->multicastlist[i], ha->da_addr,
+				ETH_ALEN);
+		ha = ha->next;
+	}
+#endif
 
 	return mc_count;
 }
