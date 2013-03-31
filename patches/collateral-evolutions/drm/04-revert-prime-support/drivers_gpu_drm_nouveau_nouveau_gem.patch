--- a/drivers/gpu/drm/nouveau/nouveau_gem.c
+++ b/drivers/gpu/drm/nouveau/nouveau_gem.c
@@ -55,8 +55,10 @@
 		nouveau_bo_unpin(nvbo);
 	}
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0))
 	if (gem->import_attach)
 		drm_prime_gem_destroy(gem, nvbo->bo.sg);
+#endif
 
 	ttm_bo_unref(&bo);
 
