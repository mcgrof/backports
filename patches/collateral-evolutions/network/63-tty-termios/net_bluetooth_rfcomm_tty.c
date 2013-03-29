--- a/net/bluetooth/rfcomm/tty.c
+++ b/net/bluetooth/rfcomm/tty.c
@@ -868,7 +868,11 @@
 
 static void rfcomm_tty_set_termios(struct tty_struct *tty, struct ktermios *old)
 {
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,7,0))
 	struct ktermios *new = &tty->termios;
+#else
+	struct ktermios *new = tty->termios;
+#endif
 	int old_baud_rate = tty_termios_baud_rate(old);
 	int new_baud_rate = tty_termios_baud_rate(new);
 
