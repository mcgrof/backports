--- a/drivers/net/wireless/libertas/mesh.c
+++ b/drivers/net/wireless/libertas/mesh.c
@@ -1015,7 +1015,7 @@
 	mesh_dev->ieee80211_ptr = mesh_wdev;
 	priv->mesh_dev = mesh_dev;
 
-	mesh_dev->netdev_ops = &mesh_netdev_ops;
+	netdev_attach_ops(mesh_dev, &mesh_netdev_ops);
 	mesh_dev->ethtool_ops = &lbs_ethtool_ops;
 	memcpy(mesh_dev->dev_addr, priv->dev->dev_addr, ETH_ALEN);
 
