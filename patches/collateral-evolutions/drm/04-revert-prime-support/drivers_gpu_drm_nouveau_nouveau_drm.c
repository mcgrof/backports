--- a/drivers/gpu/drm/nouveau/nouveau_drm.c
+++ b/drivers/gpu/drm/nouveau/nouveau_drm.c
@@ -662,7 +662,10 @@
 	.driver_features =
 		DRIVER_USE_AGP | DRIVER_PCI_DMA | DRIVER_SG |
 		DRIVER_HAVE_IRQ | DRIVER_IRQ_SHARED | DRIVER_GEM |
-		DRIVER_MODESET | DRIVER_PRIME,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0))
+		DRIVER_PRIME |
+#endif
+		DRIVER_MODESET,
 
 	.load = nouveau_drm_load,
 	.unload = nouveau_drm_unload,
@@ -688,6 +691,7 @@
 	.ioctls = nouveau_ioctls,
 	.fops = &nouveau_driver_fops,
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0))
 	.prime_handle_to_fd = drm_gem_prime_handle_to_fd,
 	.prime_fd_to_handle = drm_gem_prime_fd_to_handle,
 	.gem_prime_export = drm_gem_prime_export,
@@ -697,6 +701,7 @@
 	.gem_prime_import_sg_table = nouveau_gem_prime_import_sg_table,
 	.gem_prime_vmap = nouveau_gem_prime_vmap,
 	.gem_prime_vunmap = nouveau_gem_prime_vunmap,
+#endif
 
 	.gem_init_object = nouveau_gem_object_new,
 	.gem_free_object = nouveau_gem_object_del,
