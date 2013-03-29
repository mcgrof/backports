--- a/drivers/net/wireless/libertas/main.c
+++ b/drivers/net/wireless/libertas/main.c
@@ -993,7 +993,7 @@
 	wdev->netdev = dev;
 	priv->dev = dev;
 
- 	dev->netdev_ops = &lbs_netdev_ops;
+	netdev_attach_ops(dev, &lbs_netdev_ops);
 	dev->watchdog_timeo = 5 * HZ;
 	dev->ethtool_ops = &lbs_ethtool_ops;
 	dev->flags |= IFF_BROADCAST | IFF_MULTICAST;
