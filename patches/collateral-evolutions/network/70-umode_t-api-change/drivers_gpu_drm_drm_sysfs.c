--- a/drivers/gpu/drm/drm_sysfs.c
+++ b/drivers/gpu/drm/drm_sysfs.c
@@ -72,7 +72,11 @@
 	return 0;
 }
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,3,0))
 static char *drm_devnode(struct device *dev, umode_t *mode)
+#else
+static char *drm_devnode(struct device *dev, mode_t *mode)
+#endif
 {
 	return kasprintf(GFP_KERNEL, "dri/%s", dev_name(dev));
 }
