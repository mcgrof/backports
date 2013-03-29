--- a/drivers/net/wireless/mwifiex/sdio.c
+++ b/drivers/net/wireless/mwifiex/sdio.c
@@ -129,8 +129,10 @@
 	wait_for_completion(&adapter->fw_load);
 
 	if (user_rmmod) {
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34))
 		if (adapter->is_suspended)
 			mwifiex_sdio_resume(adapter->dev);
+#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34)) */
 
 		for (i = 0; i < adapter->priv_num; i++)
 			if ((GET_BSS_ROLE(adapter->priv[i]) ==
@@ -147,6 +149,7 @@
 	kfree(card);
 }
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34))
 /*
  * SDIO suspend.
  *
@@ -246,6 +249,7 @@
 
 	return 0;
 }
+#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34)) */
 
 /* Device ID for SD8786 */
 #define SDIO_DEVICE_ID_MARVELL_8786   (0x9116)
@@ -264,10 +268,12 @@
 
 MODULE_DEVICE_TABLE(sdio, mwifiex_ids);
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34))
 static const struct dev_pm_ops mwifiex_sdio_pm_ops = {
 	.suspend = mwifiex_sdio_suspend,
 	.resume = mwifiex_sdio_resume,
 };
+#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34)) */
 
 static struct sdio_driver mwifiex_sdio = {
 	.name = "mwifiex_sdio",
@@ -276,7 +282,9 @@
 	.remove = mwifiex_sdio_remove,
 	.drv = {
 		.owner = THIS_MODULE,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34))
 		.pm = &mwifiex_sdio_pm_ops,
+#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34)) */
 	}
 };
 
