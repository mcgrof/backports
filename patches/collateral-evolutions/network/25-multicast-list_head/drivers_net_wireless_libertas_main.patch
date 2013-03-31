--- a/drivers/net/wireless/libertas/main.c
+++ b/drivers/net/wireless/libertas/main.c
@@ -349,18 +349,34 @@
 	netif_addr_lock_bh(dev);
 	cnt = netdev_mc_count(dev);
 	netdev_for_each_mc_addr(ha, dev) {
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 		if (mac_in_list(cmd->maclist, nr_addrs, ha->addr)) {
+#else
+		if (mac_in_list(cmd->maclist, nr_addrs, ha->dmi_addr)) {
+#endif
 			lbs_deb_net("mcast address %s:%pM skipped\n", dev->name,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 				    ha->addr);
+#else
+				    ha->dmi_addr);
+#endif
 			cnt--;
 			continue;
 		}
 
 		if (i == MRVDRV_MAX_MULTICAST_LIST_SIZE)
 			break;
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 		memcpy(&cmd->maclist[6*i], ha->addr, ETH_ALEN);
+#else
+		memcpy(&cmd->maclist[6*i], ha->dmi_addr, ETH_ALEN);
+#endif
 		lbs_deb_net("mcast address %s:%pM added to filter\n", dev->name,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 			    ha->addr);
+#else
+			    ha->dmi_addr);
+#endif
 		i++;
 		cnt--;
 	}
