--- a/drivers/gpu/drm/nouveau/core/include/core/subdev.h
+++ b/drivers/gpu/drm/nouveau/core/include/core/subdev.h
@@ -20,7 +20,7 @@
 static inline struct nouveau_subdev *
 nv_subdev(void *obj)
 {
-#if CONFIG_NOUVEAU_DEBUG >= NV_DBG_PARANOIA
+#if CONFIG_COMPAT_NOUVEAU_DEBUG >= NV_DBG_PARANOIA
 	if (unlikely(!nv_iclass(obj, NV_SUBDEV_CLASS)))
 		nv_assert("BAD CAST -> NvSubDev, %08x", nv_hclass(obj));
 #endif
