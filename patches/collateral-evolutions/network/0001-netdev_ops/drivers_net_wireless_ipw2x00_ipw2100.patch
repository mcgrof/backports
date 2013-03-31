--- a/drivers/net/wireless/ipw2x00/ipw2100.c
+++ b/drivers/net/wireless/ipw2x00/ipw2100.c
@@ -6086,7 +6086,7 @@
 	priv->ieee->perfect_rssi = -20;
 	priv->ieee->worst_rssi = -85;
 
-	dev->netdev_ops = &ipw2100_netdev_ops;
+	netdev_attach_ops(dev, &ipw2100_netdev_ops);
 	dev->ethtool_ops = &ipw2100_ethtool_ops;
 	dev->wireless_handlers = &ipw2100_wx_handler_def;
 	priv->wireless_data.libipw = priv->ieee;
