--- a/drivers/gpu/drm/ttm/ttm_memory.c
+++ b/drivers/gpu/drm/ttm/ttm_memory.c
@@ -25,11 +25,13 @@
  *
  **************************************************************************/
 
+#undef pr_fmt
 #define pr_fmt(fmt) "[TTM] " fmt
 
 #include <drm/ttm/ttm_memory.h>
 #include <drm/ttm/ttm_module.h>
 #include <drm/ttm/ttm_page_alloc.h>
+#include <linux/printk.h>
 #include <linux/spinlock.h>
 #include <linux/sched.h>
 #include <linux/wait.h>
