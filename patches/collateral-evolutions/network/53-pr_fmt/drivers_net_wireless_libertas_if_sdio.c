--- a/drivers/net/wireless/libertas/if_sdio.c
+++ b/drivers/net/wireless/libertas/if_sdio.c
@@ -26,9 +26,11 @@
  * if_sdio_card_to_host() to pad the data.
  */
 
+#undef pr_fmt
 #define pr_fmt(fmt) KBUILD_MODNAME ": " fmt
 
 #include <linux/kernel.h>
+#include <linux/printk.h>
 #include <linux/module.h>
 #include <linux/slab.h>
 #include <linux/firmware.h>
