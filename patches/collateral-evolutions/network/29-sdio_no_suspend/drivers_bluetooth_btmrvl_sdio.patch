--- a/drivers/bluetooth/btmrvl_sdio.c
+++ b/drivers/bluetooth/btmrvl_sdio.c
@@ -1050,6 +1050,7 @@
 	}
 }
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34))
 static int btmrvl_sdio_suspend(struct device *dev)
 {
 	struct sdio_func *func = dev_to_sdio_func(dev);
@@ -1145,6 +1146,7 @@
 	.suspend	= btmrvl_sdio_suspend,
 	.resume		= btmrvl_sdio_resume,
 };
+#endif
 
 static struct sdio_driver bt_mrvl_sdio = {
 	.name		= "btmrvl_sdio",
@@ -1153,7 +1155,9 @@
 	.remove		= btmrvl_sdio_remove,
 	.drv = {
 		.owner = THIS_MODULE,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34))
 		.pm = &btmrvl_sdio_pm_ops,
+#endif
 	}
 };
 
