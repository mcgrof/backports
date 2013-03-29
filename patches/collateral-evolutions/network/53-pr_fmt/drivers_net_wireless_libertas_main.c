--- a/drivers/net/wireless/libertas/main.c
+++ b/drivers/net/wireless/libertas/main.c
@@ -4,8 +4,10 @@
  * thread etc..
  */
 
+#undef pr_fmt
 #define pr_fmt(fmt) KBUILD_MODNAME ": " fmt
 
+#include <linux/printk.h>
 #include <linux/module.h>
 #include <linux/delay.h>
 #include <linux/etherdevice.h>
