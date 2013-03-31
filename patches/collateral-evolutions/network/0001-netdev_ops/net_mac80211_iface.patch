--- a/net/mac80211/iface.c
+++ b/net/mac80211/iface.c
@@ -1017,7 +1017,7 @@
 {
 	ether_setup(dev);
 	dev->priv_flags &= ~IFF_TX_SKB_SHARING;
-	dev->netdev_ops = &ieee80211_dataif_ops;
+	netdev_attach_ops(dev, &ieee80211_dataif_ops);
 	dev->destructor = free_netdev;
 }
 
@@ -1180,7 +1180,7 @@
 
 	/* only monitor/p2p-device differ */
 	if (sdata->dev) {
-		sdata->dev->netdev_ops = &ieee80211_dataif_ops;
+		netdev_attach_ops(sdata->dev, &ieee80211_dataif_ops);
 		sdata->dev->type = ARPHRD_ETHER;
 	}
 
@@ -1218,7 +1218,7 @@
 		break;
 	case NL80211_IFTYPE_MONITOR:
 		sdata->dev->type = ARPHRD_IEEE80211_RADIOTAP;
-		sdata->dev->netdev_ops = &ieee80211_monitorif_ops;
+		netdev_attach_ops(sdata->dev, &ieee80211_monitorif_ops);
 		sdata->u.mntr_flags = MONITOR_FLAG_CONTROL |
 				      MONITOR_FLAG_OTHER_BSS;
 		break;
