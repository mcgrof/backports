--- a/drivers/net/wireless/ath/ath5k/led.c
+++ b/drivers/net/wireless/ath/ath5k/led.c
@@ -39,8 +39,10 @@
  *
  */
 
+#undef pr_fmt
 #define pr_fmt(fmt) KBUILD_MODNAME ": " fmt
 
+#include <linux/printk.h>
 #include <linux/pci.h>
 #include "ath5k.h"
 
