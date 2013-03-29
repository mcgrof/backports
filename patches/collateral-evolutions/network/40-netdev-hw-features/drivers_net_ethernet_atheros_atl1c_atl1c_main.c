--- a/drivers/net/ethernet/atheros/atl1c/atl1c_main.c
+++ b/drivers/net/ethernet/atheros/atl1c/atl1c_main.c
@@ -491,6 +491,7 @@
 		roundup(mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN, 8) : AT_RX_BUF_SIZE;
 }
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39))
 static netdev_features_t atl1c_fix_features(struct net_device *netdev,
 	netdev_features_t features)
 {
@@ -519,6 +520,7 @@
 
 	return 0;
 }
+#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39)) */
 
 /**
  * atl1c_change_mtu - Change the Maximum Transfer Unit
@@ -551,8 +553,19 @@
 		netdev->mtu = new_mtu;
 		adapter->hw.max_frame_size = new_mtu;
 		atl1c_set_rxbufsize(adapter, netdev);
+#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39))
+		if (new_mtu > MAX_TSO_FRAME_SIZE) {
+			adapter->netdev->features &= ~NETIF_F_TSO;
+			adapter->netdev->features &= ~NETIF_F_TSO6;
+		} else {
+			adapter->netdev->features |= NETIF_F_TSO;
+			adapter->netdev->features |= NETIF_F_TSO6;
+		}
+#endif /* (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39)) */
 		atl1c_down(adapter);
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39))
 		netdev_update_features(netdev);
+#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39)) */
 		atl1c_up(adapter);
 		clear_bit(__AT_RESETTING, &adapter->flags);
 	}
@@ -2459,8 +2472,10 @@
 	.ndo_set_mac_address	= atl1c_set_mac_addr,
 	.ndo_set_rx_mode	= atl1c_set_multi,
 	.ndo_change_mtu		= atl1c_change_mtu,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39))
 	.ndo_fix_features	= atl1c_fix_features,
 	.ndo_set_features	= atl1c_set_features,
+#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39)) */
 	.ndo_do_ioctl		= atl1c_ioctl,
 	.ndo_tx_timeout		= atl1c_tx_timeout,
 	.ndo_get_stats		= atl1c_get_stats,
@@ -2479,6 +2494,7 @@
 	atl1c_set_ethtool_ops(netdev);
 
 	/* TODO: add when ready */
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39))
 	netdev->hw_features =	NETIF_F_SG	   |
 				NETIF_F_HW_CSUM	   |
 				NETIF_F_HW_VLAN_RX |
@@ -2486,6 +2502,14 @@
 				NETIF_F_TSO6;
 	netdev->features =	netdev->hw_features |
 				NETIF_F_HW_VLAN_TX;
+#else
+	netdev->features =	NETIF_F_SG	   |
+				NETIF_F_HW_CSUM	   |
+				NETIF_F_HW_VLAN_TX |
+				NETIF_F_HW_VLAN_RX |
+				NETIF_F_TSO	   |
+				NETIF_F_TSO6;
+#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39)) */
 	return 0;
 }
 
