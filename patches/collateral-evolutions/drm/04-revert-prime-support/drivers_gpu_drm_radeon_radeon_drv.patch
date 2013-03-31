--- a/drivers/gpu/drm/radeon/radeon_drv.c
+++ b/drivers/gpu/drm/radeon/radeon_drv.c
@@ -374,8 +374,10 @@
 static struct drm_driver kms_driver = {
 	.driver_features =
 	    DRIVER_USE_AGP | DRIVER_USE_MTRR | DRIVER_PCI_DMA | DRIVER_SG |
-	    DRIVER_HAVE_IRQ | DRIVER_HAVE_DMA | DRIVER_IRQ_SHARED | DRIVER_GEM |
-	    DRIVER_PRIME,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0))
+	    DRIVER_PRIME |
+#endif
+	    DRIVER_HAVE_IRQ | DRIVER_HAVE_DMA | DRIVER_IRQ_SHARED | DRIVER_GEM,
 	.dev_priv_size = 0,
 	.load = radeon_driver_load_kms,
 	.firstopen = radeon_driver_firstopen_kms,
@@ -410,6 +412,7 @@
 	.dumb_destroy = radeon_mode_dumb_destroy,
 	.fops = &radeon_driver_kms_fops,
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0))
 	.prime_handle_to_fd = drm_gem_prime_handle_to_fd,
 	.prime_fd_to_handle = drm_gem_prime_fd_to_handle,
 	.gem_prime_export = drm_gem_prime_export,
@@ -419,6 +422,7 @@
 	.gem_prime_import_sg_table = radeon_gem_prime_import_sg_table,
 	.gem_prime_vmap = radeon_gem_prime_vmap,
 	.gem_prime_vunmap = radeon_gem_prime_vunmap,
+#endif
 
 	.name = DRIVER_NAME,
 	.desc = DRIVER_DESC,
