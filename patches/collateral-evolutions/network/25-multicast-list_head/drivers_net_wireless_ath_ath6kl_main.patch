--- a/drivers/net/wireless/ath/ath6kl/main.c
+++ b/drivers/net/wireless/ath/ath6kl/main.c
@@ -1205,7 +1205,11 @@
 	list_for_each_entry_safe(mc_filter, tmp, &vif->mc_filter, list) {
 		found = false;
 		netdev_for_each_mc_addr(ha, ndev) {
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 			if (memcmp(ha->addr, mc_filter->hw_addr,
+#else
+			if (memcmp(ha->dmi_addr, mc_filter->hw_addr,
+#endif
 				   ATH6KL_MCAST_FILTER_MAC_ADDR_SIZE) == 0) {
 				found = true;
 				break;
@@ -1239,7 +1243,11 @@
 	netdev_for_each_mc_addr(ha, ndev) {
 		found = false;
 		list_for_each_entry(mc_filter, &vif->mc_filter, list) {
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 			if (memcmp(ha->addr, mc_filter->hw_addr,
+#else
+			if (memcmp(ha->dmi_addr, mc_filter->hw_addr,
+#endif
 				   ATH6KL_MCAST_FILTER_MAC_ADDR_SIZE) == 0) {
 				found = true;
 				break;
@@ -1254,7 +1262,11 @@
 				goto out;
 			}
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 			memcpy(mc_filter->hw_addr, ha->addr,
+#else
+			memcpy(mc_filter->hw_addr, ha->dmi_addr,
+#endif
 			       ATH6KL_MCAST_FILTER_MAC_ADDR_SIZE);
 			/* Set the multicast filter */
 			ath6kl_dbg(ATH6KL_DBG_TRC,
