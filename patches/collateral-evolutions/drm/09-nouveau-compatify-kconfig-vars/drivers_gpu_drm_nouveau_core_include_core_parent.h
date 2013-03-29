--- a/drivers/gpu/drm/nouveau/core/include/core/parent.h
+++ b/drivers/gpu/drm/nouveau/core/include/core/parent.h
@@ -29,7 +29,7 @@
 static inline struct nouveau_parent *
 nv_parent(void *obj)
 {
-#if CONFIG_NOUVEAU_DEBUG >= NV_DBG_PARANOIA
+#if CONFIG_COMPAT_NOUVEAU_DEBUG >= NV_DBG_PARANOIA
 	if (unlikely(!(nv_iclass(obj, NV_PARENT_CLASS))))
 		nv_assert("BAD CAST -> NvParent, %08x", nv_hclass(obj));
 #endif
