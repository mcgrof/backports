--- a/drivers/net/wireless/iwlwifi/mvm/d3.c
+++ b/drivers/net/wireless/iwlwifi/mvm/d3.c
@@ -101,7 +101,11 @@
 	int idx = 0;
 
 	read_lock_bh(&idev->lock);
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 	list_for_each_entry(ifa, &idev->addr_list, if_list) {
+#else
+	for (ifa = idev->addr_list; ifa; ifa = ifa->if_next) {
+#endif
 		mvmvif->target_ipv6_addrs[idx] = ifa->addr;
 		idx++;
 		if (idx >= IWL_PROTO_OFFLOAD_NUM_IPV6_ADDRS)
