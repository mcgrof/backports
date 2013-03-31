--- a/drivers/net/wireless/orinoco/main.c
+++ b/drivers/net/wireless/orinoco/main.c
@@ -2272,9 +2272,9 @@
 #endif
 	/* Default to standard ops if not set */
 	if (ops)
-		dev->netdev_ops = ops;
+		netdev_attach_ops(dev, ops);
 	else
-		dev->netdev_ops = &orinoco_netdev_ops;
+		netdev_attach_ops(dev, &orinoco_netdev_ops);
 
 	/* we use the default eth_mac_addr for setting the MAC addr */
 
