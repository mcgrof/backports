--- a/drivers/net/wireless/ath/ath5k/reset.c
+++ b/drivers/net/wireless/ath/ath5k/reset.c
@@ -23,10 +23,12 @@
   Reset function and helpers
 \****************************/
 
+#undef pr_fmt
 #define pr_fmt(fmt) KBUILD_MODNAME ": " fmt
 
 #include <asm/unaligned.h>
 
+#include <linux/printk.h>
 #include <linux/pci.h>		/* To determine if a card is pci-e */
 #include <linux/log2.h>
 #include <linux/platform_device.h>
