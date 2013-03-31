--- a/drivers/net/wireless/ipw2x00/ipw2200.c
+++ b/drivers/net/wireless/ipw2x00/ipw2200.c
@@ -11680,7 +11680,7 @@
 	memcpy(priv->prom_net_dev->dev_addr, priv->mac_addr, ETH_ALEN);
 
 	priv->prom_net_dev->type = ARPHRD_IEEE80211_RADIOTAP;
-	priv->prom_net_dev->netdev_ops = &ipw_prom_netdev_ops;
+	netdev_attach_ops(priv->prom_net_dev, &ipw_prom_netdev_ops);
 
 	priv->prom_priv->ieee->iw_mode = IW_MODE_MONITOR;
 	SET_NETDEV_DEV(priv->prom_net_dev, &priv->pci_dev->dev);
@@ -11818,7 +11818,7 @@
 	priv->ieee->perfect_rssi = -20;
 	priv->ieee->worst_rssi = -85;
 
-	net_dev->netdev_ops = &ipw_netdev_ops;
+	netdev_attach_ops(net_dev, &ipw_netdev_ops);
 	priv->wireless_data.spy_data = &priv->ieee->spy_data;
 	net_dev->wireless_data = &priv->wireless_data;
 	net_dev->wireless_handlers = &ipw_wx_handler_def;
