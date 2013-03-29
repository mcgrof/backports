--- a/drivers/gpu/drm/nouveau/core/include/core/engctx.h
+++ b/drivers/gpu/drm/nouveau/core/include/core/engctx.h
@@ -20,7 +20,7 @@
 static inline struct nouveau_engctx *
 nv_engctx(void *obj)
 {
-#if CONFIG_NOUVEAU_DEBUG >= NV_DBG_PARANOIA
+#if CONFIG_COMPAT_NOUVEAU_DEBUG >= NV_DBG_PARANOIA
 	if (unlikely(!nv_iclass(obj, NV_ENGCTX_CLASS)))
 		nv_assert("BAD CAST -> NvEngCtx, %08x", nv_hclass(obj));
 #endif
