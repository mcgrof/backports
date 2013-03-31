--- a/drivers/net/wireless/ath/ath5k/dma.c
+++ b/drivers/net/wireless/ath/ath5k/dma.c
@@ -29,8 +29,11 @@
  * status registers (ISR).
  */
 
+#undef pr_fmt
 #define pr_fmt(fmt) KBUILD_MODNAME ": " fmt
 
+#include <linux/printk.h>
+
 #include "ath5k.h"
 #include "reg.h"
 #include "debug.h"
