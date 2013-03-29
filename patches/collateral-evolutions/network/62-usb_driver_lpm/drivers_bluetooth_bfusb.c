--- a/drivers/bluetooth/bfusb.c
+++ b/drivers/bluetooth/bfusb.c
@@ -745,7 +745,9 @@
 	.probe		= bfusb_probe,
 	.disconnect	= bfusb_disconnect,
 	.id_table	= bfusb_table,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,5,0))
 	.disable_hub_initiated_lpm = 1,
+#endif
 };
 
 module_usb_driver(bfusb_driver);
