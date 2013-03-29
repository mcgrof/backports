--- a/drivers/net/wireless/ath/ath5k/mac80211-ops.c
+++ b/drivers/net/wireless/ath/ath5k/mac80211-ops.c
@@ -41,11 +41,14 @@
  *
  */
 
+#undef pr_fmt
 #define pr_fmt(fmt) KBUILD_MODNAME ": " fmt
 
 #include <net/mac80211.h>
 #include <asm/unaligned.h>
 
+#include <linux/printk.h>
+
 #include "ath5k.h"
 #include "base.h"
 #include "reg.h"
