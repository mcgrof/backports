--- a/drivers/net/wireless/mwifiex/sta_ioctl.c
+++ b/drivers/net/wireless/mwifiex/sta_ioctl.c
@@ -43,7 +43,11 @@
 	struct netdev_hw_addr *ha;
 
 	netdev_for_each_mc_addr(ha, dev)
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 		memcpy(&mlist->mac_list[i++], ha->addr, ETH_ALEN);
+#else
+		memcpy(&mlist->mac_list[i++], ha->dmi_addr, ETH_ALEN);
+#endif
 
 	return i;
 }
