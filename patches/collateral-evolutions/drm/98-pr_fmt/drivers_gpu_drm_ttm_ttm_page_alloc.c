--- a/drivers/gpu/drm/ttm/ttm_page_alloc.c
+++ b/drivers/gpu/drm/ttm/ttm_page_alloc.c
@@ -31,8 +31,10 @@
  * - doesn't track currently in use pages
  */
 
+#undef pr_fmt
 #define pr_fmt(fmt) "[TTM] " fmt
 
+#include <linux/printk.h>
 #include <linux/list.h>
 #include <linux/spinlock.h>
 #include <linux/highmem.h>
