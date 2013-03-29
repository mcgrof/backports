--- a/net/bluetooth/hci_sock.c
+++ b/net/bluetooth/hci_sock.c
@@ -884,8 +884,13 @@
 	goto done;
 }
 
+#if (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,31))
 static int hci_sock_setsockopt(struct socket *sock, int level, int optname,
 			       char __user *optval, unsigned int len)
+#else
+static int hci_sock_setsockopt(struct socket *sock, int level, int optname,
+			       char __user *optval, int len)
+#endif
 {
 	struct hci_ufilter uf = { .opcode = 0 };
 	struct sock *sk = sock->sk;
@@ -1059,8 +1064,12 @@
 	.obj_size	= sizeof(struct hci_pinfo)
 };
 
+#if defined(CONFIG_COMPAT_BT_SOCK_CREATE_NEEDS_KERN)
 static int hci_sock_create(struct net *net, struct socket *sock, int protocol,
 			   int kern)
+#else
+static int hci_sock_create(struct net *net, struct socket *sock, int protocol)
+#endif
 {
 	struct sock *sk;
 
