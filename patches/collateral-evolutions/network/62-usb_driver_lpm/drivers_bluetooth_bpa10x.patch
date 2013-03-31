--- a/drivers/bluetooth/bpa10x.c
+++ b/drivers/bluetooth/bpa10x.c
@@ -504,7 +504,9 @@
 	.probe		= bpa10x_probe,
 	.disconnect	= bpa10x_disconnect,
 	.id_table	= bpa10x_table,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,5,0))
 	.disable_hub_initiated_lpm = 1,
+#endif
 };
 
 module_usb_driver(bpa10x_driver);
