--- a/drivers/net/ethernet/atheros/atl1c/atl1c_main.c
+++ b/drivers/net/ethernet/atheros/atl1c/atl1c_main.c
@@ -410,7 +410,11 @@
 
 	/* comoute mc addresses' hash value ,and put it into hash table */
 	netdev_for_each_mc_addr(ha, netdev) {
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 		hash_value = atl1c_hash_mc_addr(hw, ha->addr);
+#else
+		hash_value = atl1c_hash_mc_addr(hw, ha->dmi_addr);
+#endif
 		atl1c_hash_set(hw, hash_value);
 	}
 }
