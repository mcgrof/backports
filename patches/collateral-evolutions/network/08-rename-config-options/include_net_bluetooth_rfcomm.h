--- a/include/net/bluetooth/rfcomm.h
+++ b/include/net/bluetooth/rfcomm.h
@@ -351,7 +351,7 @@
 
 int  rfcomm_dev_ioctl(struct sock *sk, unsigned int cmd, void __user *arg);
 
-#ifdef CONFIG_BT_RFCOMM_TTY
+#ifdef CONFIG_COMPAT_BT_RFCOMM_TTY
 int  rfcomm_init_ttys(void);
 void rfcomm_cleanup_ttys(void);
 #else
