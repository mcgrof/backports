--- a/drivers/gpu/drm/nouveau/core/include/core/printk.h
+++ b/drivers/gpu/drm/nouveau/core/include/core/printk.h
@@ -19,7 +19,7 @@
 nv_printk_(struct nouveau_object *, const char *, int, const char *, ...);
 
 #define nv_printk(o,l,f,a...) do {                                             \
-	if (NV_DBG_##l <= CONFIG_NOUVEAU_DEBUG)                                \
+	if (NV_DBG_##l <= CONFIG_COMPAT_NOUVEAU_DEBUG)                                \
 		nv_printk_(nv_object(o), NV_PRINTK_##l, NV_DBG_##l, f, ##a);   \
 } while(0)
 
@@ -32,7 +32,7 @@
 #define nv_spam(o,f,a...) nv_printk((o), SPAM, f, ##a)
 
 #define nv_assert(f,a...) do {                                                 \
-	if (NV_DBG_FATAL <= CONFIG_NOUVEAU_DEBUG)                              \
+	if (NV_DBG_FATAL <= CONFIG_COMPAT_NOUVEAU_DEBUG)                              \
 		nv_printk_(NULL, NV_PRINTK_FATAL, NV_DBG_FATAL, f "\n", ##a);  \
 	BUG_ON(1);                                                             \
 } while(0)
