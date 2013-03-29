--- a/drivers/gpu/drm/i915/i915_gem_dmabuf.c
+++ b/drivers/gpu/drm/i915/i915_gem_dmabuf.c
@@ -216,10 +216,14 @@
 	.kmap_atomic = i915_gem_dmabuf_kmap_atomic,
 	.kunmap = i915_gem_dmabuf_kunmap,
 	.kunmap_atomic = i915_gem_dmabuf_kunmap_atomic,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,5,0))
 	.mmap = i915_gem_dmabuf_mmap,
 	.vmap = i915_gem_dmabuf_vmap,
 	.vunmap = i915_gem_dmabuf_vunmap,
+#endif
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0))
 	.begin_cpu_access = i915_gem_begin_cpu_access,
+#endif
 };
 
 struct dma_buf *i915_gem_prime_export(struct drm_device *dev,
