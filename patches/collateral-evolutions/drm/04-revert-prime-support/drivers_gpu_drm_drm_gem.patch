--- a/drivers/gpu/drm/drm_gem.c
+++ b/drivers/gpu/drm/drm_gem.c
@@ -35,7 +35,9 @@
 #include <linux/mman.h>
 #include <linux/pagemap.h>
 #include <linux/shmem_fs.h>
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0))
 #include <linux/dma-buf.h>
+#endif
 #include <drm/drmP.h>
 
 /** @file drm_gem.c
@@ -204,6 +206,7 @@
 static void
 drm_gem_remove_prime_handles(struct drm_gem_object *obj, struct drm_file *filp)
 {
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0))
 	if (obj->import_attach) {
 		drm_prime_remove_imported_buf_handle(&filp->prime,
 				obj->import_attach->dmabuf);
@@ -212,6 +215,7 @@
 		drm_prime_remove_imported_buf_handle(&filp->prime,
 				obj->export_dma_buf);
 	}
+#endif
 }
 
 /**
