--- a/net/bluetooth/cmtp/capi.c
+++ b/net/bluetooth/cmtp/capi.c
@@ -384,7 +384,11 @@
 
 	BT_DBG("ctrl %p", ctrl);
 
+#if (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,30))
 	capi_ctr_down(ctrl);
+#else
+	capi_ctr_reseted(ctrl);
+#endif
 
 	atomic_inc(&session->terminate);
 	wake_up_process(session->task);
