--- a/drivers/gpu/drm/nouveau/core/include/core/client.h
+++ b/drivers/gpu/drm/nouveau/core/include/core/client.h
@@ -15,7 +15,7 @@
 static inline struct nouveau_client *
 nv_client(void *obj)
 {
-#if CONFIG_NOUVEAU_DEBUG >= NV_DBG_PARANOIA
+#if CONFIG_COMPAT_NOUVEAU_DEBUG >= NV_DBG_PARANOIA
 	if (unlikely(!nv_iclass(obj, NV_CLIENT_CLASS)))
 		nv_assert("BAD CAST -> NvClient, %08x", nv_hclass(obj));
 #endif
