--- a/drivers/gpu/drm/nouveau/core/include/core/device.h
+++ b/drivers/gpu/drm/nouveau/core/include/core/device.h
@@ -97,7 +97,7 @@
 	if (device->parent)
 		device = device->parent;
 
-#if CONFIG_NOUVEAU_DEBUG >= NV_DBG_PARANOIA
+#if CONFIG_COMPAT_NOUVEAU_DEBUG >= NV_DBG_PARANOIA
 	if (unlikely(!nv_iclass(device, NV_SUBDEV_CLASS) ||
 		     (nv_hclass(device) & 0xff) != NVDEV_SUBDEV_DEVICE)) {
 		nv_assert("BAD CAST -> NvDevice, 0x%08x 0x%08x",
