--- a/drivers/net/wireless/libertas/defs.h
+++ b/drivers/net/wireless/libertas/defs.h
@@ -16,6 +16,14 @@
 #define DRV_NAME "libertas"
 #endif
 
+/*
+ * Really nasty hack to avoid stuffing compat.diff with tons of ifdefs,
+ * we could add this to a compat header file but too lazy to check ml_priv
+ * is not used anywhere else
+ */
+#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,26))
+#define ml_priv priv
+#endif
 
 #define LBS_DEB_ENTER	0x00000001
 #define LBS_DEB_LEAVE	0x00000002
