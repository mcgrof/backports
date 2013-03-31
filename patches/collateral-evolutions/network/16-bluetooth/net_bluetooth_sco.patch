--- a/net/bluetooth/sco.c
+++ b/net/bluetooth/sco.c
@@ -423,8 +423,12 @@
 	return sk;
 }
 
+#if defined(CONFIG_COMPAT_BT_SOCK_CREATE_NEEDS_KERN)
 static int sco_sock_create(struct net *net, struct socket *sock, int protocol,
 			   int kern)
+#else
+static int sco_sock_create(struct net *net, struct socket *sock, int protocol)
+#endif
 {
 	struct sock *sk;
 
@@ -675,7 +679,11 @@
 	return bt_sock_recvmsg(iocb, sock, msg, len, flags);
 }
 
+#if (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,31))
 static int sco_sock_setsockopt(struct socket *sock, int level, int optname, char __user *optval, unsigned int optlen)
+#else
+static int sco_sock_setsockopt(struct socket *sock, int level, int optname, char __user *optval, int optlen)
+#endif
 {
 	struct sock *sk = sock->sk;
 	int err = 0;
