--- a/drivers/net/wireless/orinoco/orinoco_usb.c
+++ b/drivers/net/wireless/orinoco/orinoco_usb.c
@@ -1758,7 +1758,9 @@
 	.probe = ezusb_probe,
 	.disconnect = ezusb_disconnect,
 	.id_table = ezusb_table,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,5,0))
 	.disable_hub_initiated_lpm = 1,
+#endif
 };
 
 module_usb_driver(orinoco_driver);
