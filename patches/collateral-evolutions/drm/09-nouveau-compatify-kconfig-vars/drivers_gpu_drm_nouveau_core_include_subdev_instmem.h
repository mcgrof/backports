--- a/drivers/gpu/drm/nouveau/core/include/subdev/instmem.h
+++ b/drivers/gpu/drm/nouveau/core/include/subdev/instmem.h
@@ -16,7 +16,7 @@
 static inline struct nouveau_instobj *
 nv_memobj(void *obj)
 {
-#if CONFIG_NOUVEAU_DEBUG >= NV_DBG_PARANOIA
+#if CONFIG_COMPAT_NOUVEAU_DEBUG >= NV_DBG_PARANOIA
 	if (unlikely(!nv_iclass(obj, NV_MEMOBJ_CLASS)))
 		nv_assert("BAD CAST -> NvMemObj, %08x", nv_hclass(obj));
 #endif
