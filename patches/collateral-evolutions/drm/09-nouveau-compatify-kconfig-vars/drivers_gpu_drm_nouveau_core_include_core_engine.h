--- a/drivers/gpu/drm/nouveau/core/include/core/engine.h
+++ b/drivers/gpu/drm/nouveau/core/include/core/engine.h
@@ -22,7 +22,7 @@
 static inline struct nouveau_engine *
 nv_engine(void *obj)
 {
-#if CONFIG_NOUVEAU_DEBUG >= NV_DBG_PARANOIA
+#if CONFIG_COMPAT_NOUVEAU_DEBUG >= NV_DBG_PARANOIA
 	if (unlikely(!nv_iclass(obj, NV_ENGINE_CLASS)))
 		nv_assert("BAD CAST -> NvEngine, %08x", nv_hclass(obj));
 #endif
