--- a/drivers/net/wireless/zd1211rw/zd_usb.c
+++ b/drivers/net/wireless/zd1211rw/zd_usb.c
@@ -1540,7 +1540,9 @@
 	.disconnect	= disconnect,
 	.pre_reset	= pre_reset,
 	.post_reset	= post_reset,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,5,0))
 	.disable_hub_initiated_lpm = 1,
+#endif
 };
 
 struct workqueue_struct *zd_workqueue;
