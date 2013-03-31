--- a/drivers/gpu/drm/drm_prime.c
+++ b/drivers/gpu/drm/drm_prime.c
@@ -152,9 +152,11 @@
 	.kmap_atomic = drm_gem_dmabuf_kmap_atomic,
 	.kunmap = drm_gem_dmabuf_kunmap,
 	.kunmap_atomic = drm_gem_dmabuf_kunmap_atomic,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,5,0))
 	.mmap = drm_gem_dmabuf_mmap,
 	.vmap = drm_gem_dmabuf_vmap,
 	.vunmap = drm_gem_dmabuf_vunmap,
+#endif
 };
 
 /**
