--- a/net/bluetooth/bnep/netdev.c
+++ b/net/bluetooth/bnep/netdev.c
@@ -93,8 +93,13 @@
 		netdev_for_each_mc_addr(ha, dev) {
 			if (i == BNEP_MAX_MULTICAST_FILTERS)
 				break;
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 			memcpy(__skb_put(skb, ETH_ALEN), ha->addr, ETH_ALEN);
 			memcpy(__skb_put(skb, ETH_ALEN), ha->addr, ETH_ALEN);
+#else
+			memcpy(__skb_put(skb, ETH_ALEN), ha->dmi_addr, ETH_ALEN);
+			memcpy(__skb_put(skb, ETH_ALEN), ha->dmi_addr, ETH_ALEN);
+#endif
 
 			i++;
 		}
