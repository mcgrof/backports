--- a/drivers/net/ethernet/atheros/atlx/atlx.c
+++ b/drivers/net/ethernet/atheros/atlx/atlx.c
@@ -254,6 +254,7 @@
 	atlx_vlan_mode(adapter->netdev, adapter->netdev->features);
 }
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39))
 static netdev_features_t atlx_fix_features(struct net_device *netdev,
 	netdev_features_t features)
 {
@@ -279,5 +280,6 @@
 
 	return 0;
 }
+#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39)) */
 
 #endif /* ATLX_C */
