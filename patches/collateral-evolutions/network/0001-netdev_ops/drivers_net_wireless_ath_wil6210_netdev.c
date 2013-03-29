--- a/drivers/net/wireless/ath/wil6210/netdev.c
+++ b/drivers/net/wireless/ath/wil6210/netdev.c
@@ -76,7 +76,7 @@
 		goto out_priv;
 	}
 
-	ndev->netdev_ops = &wil_netdev_ops;
+	netdev_attach_ops(ndev, &wil_netdev_ops);
 	ndev->ieee80211_ptr = wdev;
 	SET_NETDEV_DEV(ndev, wiphy_dev(wdev->wiphy));
 	wdev->netdev = ndev;
