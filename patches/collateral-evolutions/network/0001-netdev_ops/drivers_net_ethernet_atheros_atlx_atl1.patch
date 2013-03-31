--- a/drivers/net/ethernet/atheros/atlx/atl1.c
+++ b/drivers/net/ethernet/atheros/atlx/atl1.c
@@ -3009,7 +3009,7 @@
 	adapter->mii.phy_id_mask = 0x1f;
 	adapter->mii.reg_num_mask = 0x1f;
 
-	netdev->netdev_ops = &atl1_netdev_ops;
+	netdev_attach_ops(netdev, &atl1_netdev_ops);
 	netdev->watchdog_timeo = 5 * HZ;
 	netif_napi_add(netdev, &adapter->napi, atl1_rings_clean, 64);
 
