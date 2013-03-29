--- a/drivers/net/wireless/ath/ath5k/desc.c
+++ b/drivers/net/wireless/ath/ath5k/desc.c
@@ -21,8 +21,11 @@
  Hardware Descriptor Functions
 \******************************/
 
+#undef pr_fmt
 #define pr_fmt(fmt) KBUILD_MODNAME ": " fmt
 
+#include <linux/printk.h>
+
 #include "ath5k.h"
 #include "reg.h"
 #include "debug.h"
