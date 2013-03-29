--- a/drivers/net/wireless/libertas/if_spi.c
+++ b/drivers/net/wireless/libertas/if_spi.c
@@ -17,8 +17,10 @@
  * (at your option) any later version.
  */
 
+#undef pr_fmt
 #define pr_fmt(fmt) KBUILD_MODNAME ": " fmt
 
+#include <linux/printk.h>
 #include <linux/hardirq.h>
 #include <linux/interrupt.h>
 #include <linux/module.h>
