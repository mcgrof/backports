--- a/drivers/net/ethernet/broadcom/b44.c
+++ b/drivers/net/ethernet/broadcom/b44.c
@@ -2170,7 +2170,7 @@
 	bp->rx_pending = B44_DEF_RX_RING_PENDING;
 	bp->tx_pending = B44_DEF_TX_RING_PENDING;
 
-	dev->netdev_ops = &b44_netdev_ops;
+	netdev_attach_ops(dev, &b44_netdev_ops);
 	netif_napi_add(dev, &bp->napi, b44_poll, 64);
 	dev->watchdog_timeo = B44_TX_TIMEOUT;
 	dev->irq = sdev->irq;
