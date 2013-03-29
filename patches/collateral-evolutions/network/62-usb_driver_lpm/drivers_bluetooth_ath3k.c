--- a/drivers/bluetooth/ath3k.c
+++ b/drivers/bluetooth/ath3k.c
@@ -473,7 +473,9 @@
 	.probe		= ath3k_probe,
 	.disconnect	= ath3k_disconnect,
 	.id_table	= ath3k_table,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,5,0))
 	.disable_hub_initiated_lpm = 1,
+#endif
 };
 
 module_usb_driver(ath3k_driver);
