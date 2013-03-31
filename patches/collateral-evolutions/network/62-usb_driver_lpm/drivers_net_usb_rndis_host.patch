--- a/drivers/net/usb/rndis_host.c
+++ b/drivers/net/usb/rndis_host.c
@@ -642,7 +642,9 @@
 	.disconnect =	usbnet_disconnect,
 	.suspend =	usbnet_suspend,
 	.resume =	usbnet_resume,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,5,0))
 	.disable_hub_initiated_lpm = 1,
+#endif
 };
 
 module_usb_driver(rndis_driver);
