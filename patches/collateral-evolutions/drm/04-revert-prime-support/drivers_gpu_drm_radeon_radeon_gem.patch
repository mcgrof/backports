--- a/drivers/gpu/drm/radeon/radeon_gem.c
+++ b/drivers/gpu/drm/radeon/radeon_gem.c
@@ -41,8 +41,10 @@
 	struct radeon_bo *robj = gem_to_radeon_bo(gobj);
 
 	if (robj) {
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0))
 		if (robj->gem_base.import_attach)
 			drm_prime_gem_destroy(&robj->gem_base, robj->tbo.sg);
+#endif
 		radeon_bo_unref(&robj);
 	}
 }
