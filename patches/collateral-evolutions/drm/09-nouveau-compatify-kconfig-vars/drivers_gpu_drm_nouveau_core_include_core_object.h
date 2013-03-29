--- a/drivers/gpu/drm/nouveau/core/include/core/object.h
+++ b/drivers/gpu/drm/nouveau/core/include/core/object.h
@@ -20,7 +20,7 @@
 	struct nouveau_object *engine;
 	atomic_t refcount;
 	atomic_t usecount;
-#if CONFIG_NOUVEAU_DEBUG >= NV_DBG_PARANOIA
+#if CONFIG_COMPAT_NOUVEAU_DEBUG >= NV_DBG_PARANOIA
 #define NOUVEAU_OBJECT_MAGIC 0x75ef0bad
 	struct list_head list;
 	u32 _magic;
@@ -30,7 +30,7 @@
 static inline struct nouveau_object *
 nv_object(void *obj)
 {
-#if CONFIG_NOUVEAU_DEBUG >= NV_DBG_PARANOIA
+#if CONFIG_COMPAT_NOUVEAU_DEBUG >= NV_DBG_PARANOIA
 	if (likely(obj)) {
 		struct nouveau_object *object = obj;
 		if (unlikely(object->_magic != NOUVEAU_OBJECT_MAGIC))
