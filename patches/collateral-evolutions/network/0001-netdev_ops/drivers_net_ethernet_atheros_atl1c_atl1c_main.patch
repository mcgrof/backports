--- a/drivers/net/ethernet/atheros/atl1c/atl1c_main.c
+++ b/drivers/net/ethernet/atheros/atl1c/atl1c_main.c
@@ -2470,7 +2470,7 @@
 	SET_NETDEV_DEV(netdev, &pdev->dev);
 	pci_set_drvdata(pdev, netdev);
 
-	netdev->netdev_ops = &atl1c_netdev_ops;
+	netdev_attach_ops(netdev, &atl1c_netdev_ops);
 	netdev->watchdog_timeo = AT_TX_WATCHDOG;
 	atl1c_set_ethtool_ops(netdev);
 
