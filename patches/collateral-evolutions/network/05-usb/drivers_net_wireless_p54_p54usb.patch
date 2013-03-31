--- a/drivers/net/wireless/p54/p54usb.c
+++ b/drivers/net/wireless/p54/p54usb.c
@@ -1137,7 +1137,9 @@
 	.resume = p54u_resume,
 	.reset_resume = p54u_resume,
 #endif /* CONFIG_PM */
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,27))
 	.soft_unbind = 1,
+#endif
 	.disable_hub_initiated_lpm = 1,
 };
 
