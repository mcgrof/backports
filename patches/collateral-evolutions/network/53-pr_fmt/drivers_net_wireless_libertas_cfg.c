--- a/drivers/net/wireless/libertas/cfg.c
+++ b/drivers/net/wireless/libertas/cfg.c
@@ -6,8 +6,10 @@
  *
  */
 
+#undef pr_fmt
 #define pr_fmt(fmt) KBUILD_MODNAME ": " fmt
 
+#include <linux/printk.h>
 #include <linux/hardirq.h>
 #include <linux/sched.h>
 #include <linux/wait.h>
