--- a/drivers/net/wireless/mwifiex/main.c
+++ b/drivers/net/wireless/mwifiex/main.c
@@ -654,7 +654,7 @@
 void mwifiex_init_priv_params(struct mwifiex_private *priv,
 						struct net_device *dev)
 {
-	dev->netdev_ops = &mwifiex_netdev_ops;
+	netdev_attach_ops(dev, &mwifiex_netdev_ops);
 	/* Initialize private structure */
 	priv->current_key_index = 0;
 	priv->media_connected = false;