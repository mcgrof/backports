--- a/drivers/net/usb/usbnet.c
+++ b/drivers/net/usb/usbnet.c
@@ -933,7 +933,9 @@
 	.get_drvinfo		= usbnet_get_drvinfo,
 	.get_msglevel		= usbnet_get_msglevel,
 	.set_msglevel		= usbnet_set_msglevel,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,5,0))
 	.get_ts_info		= ethtool_op_get_ts_info,
+#endif
 };
 
 /*-------------------------------------------------------------------------*/
