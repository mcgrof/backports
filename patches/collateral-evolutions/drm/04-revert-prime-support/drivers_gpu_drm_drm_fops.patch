--- a/drivers/gpu/drm/drm_fops.c
+++ b/drivers/gpu/drm/drm_fops.c
@@ -284,8 +284,10 @@
 	if (dev->driver->driver_features & DRIVER_GEM)
 		drm_gem_open(dev, priv);
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0))
 	if (drm_core_check_feature(dev, DRIVER_PRIME))
 		drm_prime_init_file_private(&priv->prime);
+#endif
 
 	if (dev->driver->open) {
 		ret = dev->driver->open(dev, priv);
@@ -538,8 +540,10 @@
 	if (dev->driver->postclose)
 		dev->driver->postclose(dev, file_priv);
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0))
 	if (drm_core_check_feature(dev, DRIVER_PRIME))
 		drm_prime_destroy_file_private(&file_priv->prime);
+#endif
 
 	put_pid(file_priv->pid);
 	kfree(file_priv);
