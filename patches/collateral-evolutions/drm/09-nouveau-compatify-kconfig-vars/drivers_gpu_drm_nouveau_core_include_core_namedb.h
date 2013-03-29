--- a/drivers/gpu/drm/nouveau/core/include/core/namedb.h
+++ b/drivers/gpu/drm/nouveau/core/include/core/namedb.h
@@ -14,7 +14,7 @@
 static inline struct nouveau_namedb *
 nv_namedb(void *obj)
 {
-#if CONFIG_NOUVEAU_DEBUG >= NV_DBG_PARANOIA
+#if CONFIG_COMPAT_NOUVEAU_DEBUG >= NV_DBG_PARANOIA
 	if (unlikely(!nv_iclass(obj, NV_NAMEDB_CLASS)))
 		nv_assert("BAD CAST -> NvNameDB, %08x", nv_hclass(obj));
 #endif
