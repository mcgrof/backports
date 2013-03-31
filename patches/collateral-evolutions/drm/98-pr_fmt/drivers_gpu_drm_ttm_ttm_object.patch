--- a/drivers/gpu/drm/ttm/ttm_object.c
+++ b/drivers/gpu/drm/ttm/ttm_object.c
@@ -49,10 +49,12 @@
  * for fast lookup of ref objects given a base object.
  */
 
+#undef pr_fmt
 #define pr_fmt(fmt) "[TTM] " fmt
 
 #include <drm/ttm/ttm_object.h>
 #include <drm/ttm/ttm_module.h>
+#include <linux/printk.h>
 #include <linux/list.h>
 #include <linux/spinlock.h>
 #include <linux/slab.h>
