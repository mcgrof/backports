--- a/drivers/gpu/drm/ttm/ttm_tt.c
+++ b/drivers/gpu/drm/ttm/ttm_tt.c
@@ -28,8 +28,10 @@
  * Authors: Thomas Hellstrom <thellstrom-at-vmware-dot-com>
  */
 
+#undef pr_fmt
 #define pr_fmt(fmt) "[TTM] " fmt
 
+#include <linux/printk.h>
 #include <linux/sched.h>
 #include <linux/highmem.h>
 #include <linux/pagemap.h>
