--- a/drivers/net/wireless/at76c50x-usb.c
+++ b/drivers/net/wireless/at76c50x-usb.c
@@ -2451,7 +2451,9 @@
 	.probe = at76_probe,
 	.disconnect = at76_disconnect,
 	.id_table = dev_table,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,5,0))
 	.disable_hub_initiated_lpm = 1,
+#endif
 };
 
 static int __init at76_mod_init(void)
