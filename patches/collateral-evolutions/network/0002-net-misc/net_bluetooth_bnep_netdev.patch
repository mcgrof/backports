--- a/net/bluetooth/bnep/netdev.c
+++ b/net/bluetooth/bnep/netdev.c
@@ -161,8 +161,12 @@
 }
 #endif
 
+#if (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,31))
 static netdev_tx_t bnep_net_xmit(struct sk_buff *skb,
 				 struct net_device *dev)
+#else
+static int bnep_net_xmit(struct sk_buff *skb, struct net_device *dev)
+#endif
 {
 	struct bnep_session *s = netdev_priv(dev);
 	struct sock *sk = s->sock->sk;
