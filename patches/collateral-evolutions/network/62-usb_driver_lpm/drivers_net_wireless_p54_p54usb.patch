--- a/drivers/net/wireless/p54/p54usb.c
+++ b/drivers/net/wireless/p54/p54usb.c
@@ -1140,7 +1140,9 @@
 #if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,27))
 	.soft_unbind = 1,
 #endif
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,5,0))
 	.disable_hub_initiated_lpm = 1,
+#endif
 };
 
 module_usb_driver(p54u_driver);
