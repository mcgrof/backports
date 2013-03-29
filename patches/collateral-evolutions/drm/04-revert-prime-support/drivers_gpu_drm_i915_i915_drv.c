--- a/drivers/gpu/drm/i915/i915_drv.c
+++ b/drivers/gpu/drm/i915/i915_drv.c
@@ -1058,7 +1058,11 @@
 	 */
 	.driver_features =
 	    DRIVER_USE_AGP | DRIVER_REQUIRE_AGP | /* DRIVER_USE_MTRR |*/
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0))
 	    DRIVER_HAVE_IRQ | DRIVER_IRQ_SHARED | DRIVER_GEM | DRIVER_PRIME,
+#else
+	    DRIVER_HAVE_IRQ | DRIVER_IRQ_SHARED | DRIVER_GEM,
+#endif
 	.load = i915_driver_load,
 	.unload = i915_driver_unload,
 	.open = i915_driver_open,
@@ -1081,10 +1085,12 @@
 	.gem_free_object = i915_gem_free_object,
 	.gem_vm_ops = &i915_gem_vm_ops,
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0))
 	.prime_handle_to_fd = drm_gem_prime_handle_to_fd,
 	.prime_fd_to_handle = drm_gem_prime_fd_to_handle,
 	.gem_prime_export = i915_gem_prime_export,
 	.gem_prime_import = i915_gem_prime_import,
+#endif
 
 	.dumb_create = i915_gem_dumb_create,
 	.dumb_map_offset = i915_gem_mmap_gtt,
