--- a/drivers/gpu/drm/ttm/ttm_bo.c
+++ b/drivers/gpu/drm/ttm/ttm_bo.c
@@ -28,11 +28,13 @@
  * Authors: Thomas Hellstrom <thellstrom-at-vmware-dot-com>
  */
 
+#undef pr_fmt
 #define pr_fmt(fmt) "[TTM] " fmt
 
 #include <drm/ttm/ttm_module.h>
 #include <drm/ttm/ttm_bo_driver.h>
 #include <drm/ttm/ttm_placement.h>
+#include <linux/printk.h>
 #include <linux/jiffies.h>
 #include <linux/slab.h>
 #include <linux/sched.h>
