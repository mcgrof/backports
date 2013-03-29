--- a/drivers/net/usb/usbnet.c
+++ b/drivers/net/usb/usbnet.c
@@ -1446,7 +1446,7 @@
 		net->features |= NETIF_F_HIGHDMA;
 #endif
 
-	net->netdev_ops = &usbnet_netdev_ops;
+	netdev_attach_ops(net, &usbnet_netdev_ops);
 	net->watchdog_timeo = TX_TIMEOUT_JIFFIES;
 	net->ethtool_ops = &usbnet_ethtool_ops;
 
