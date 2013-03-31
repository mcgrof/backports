--- a/drivers/gpu/drm/drm_prime.c
+++ b/drivers/gpu/drm/drm_prime.c
@@ -26,6 +26,8 @@
  *
  */
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0))
+
 #include <linux/export.h>
 #include <linux/dma-buf.h>
 #include <drm/drmP.h>
@@ -532,3 +534,4 @@
 	mutex_unlock(&prime_fpriv->lock);
 }
 EXPORT_SYMBOL(drm_prime_remove_imported_buf_handle);
+#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0)) */
