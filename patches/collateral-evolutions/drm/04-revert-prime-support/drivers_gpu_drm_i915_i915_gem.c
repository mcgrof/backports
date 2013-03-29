--- a/drivers/gpu/drm/i915/i915_gem.c
+++ b/drivers/gpu/drm/i915/i915_gem.c
@@ -34,7 +34,9 @@
 #include <linux/slab.h>
 #include <linux/swap.h>
 #include <linux/pci.h>
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0))
 #include <linux/dma-buf.h>
+#endif
 
 static void i915_gem_object_flush_gtt_write_domain(struct drm_i915_gem_object *obj);
 static void i915_gem_object_flush_cpu_write_domain(struct drm_i915_gem_object *obj);
@@ -3825,8 +3827,10 @@
 
 	BUG_ON(obj->pages);
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0))
 	if (obj->base.import_attach)
 		drm_prime_gem_destroy(&obj->base, NULL);
+#endif
 
 	drm_gem_object_release(&obj->base);
 	i915_gem_info_remove_obj(dev_priv, obj->base.size);
