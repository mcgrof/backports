--- a/drivers/gpu/drm/ttm/ttm_page_alloc_dma.c
+++ b/drivers/gpu/drm/ttm/ttm_page_alloc_dma.c
@@ -33,8 +33,10 @@
  *   when freed).
  */
 
+#undef pr_fmt
 #define pr_fmt(fmt) "[TTM] " fmt
 
+#include <linux/printk.h>
 #include <linux/dma-mapping.h>
 #include <linux/list.h>
 #include <linux/seq_file.h> /* for seq_printf */
