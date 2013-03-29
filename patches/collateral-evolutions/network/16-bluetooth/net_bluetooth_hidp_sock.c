--- a/net/bluetooth/hidp/sock.c
+++ b/net/bluetooth/hidp/sock.c
@@ -235,8 +235,12 @@
 	.obj_size	= sizeof(struct bt_sock)
 };
 
+#if defined(CONFIG_COMPAT_BT_SOCK_CREATE_NEEDS_KERN)
 static int hidp_sock_create(struct net *net, struct socket *sock, int protocol,
 			    int kern)
+#else
+static int hidp_sock_create(struct net *net, struct socket *sock, int protocol)
+#endif
 {
 	struct sock *sk;
 
