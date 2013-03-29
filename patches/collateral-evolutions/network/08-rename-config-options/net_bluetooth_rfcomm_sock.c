--- a/net/bluetooth/rfcomm/sock.c
+++ b/net/bluetooth/rfcomm/sock.c
@@ -860,7 +860,7 @@
 	err = bt_sock_ioctl(sock, cmd, arg);
 
 	if (err == -ENOIOCTLCMD) {
-#ifdef CONFIG_BT_RFCOMM_TTY
+#ifdef CONFIG_COMPAT_BT_RFCOMM_TTY
 		lock_sock(sk);
 		err = rfcomm_dev_ioctl(sk, cmd, (void __user *) arg);
 		release_sock(sk);
