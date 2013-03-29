--- a/drivers/net/wireless/mwifiex/sdio.c
+++ b/drivers/net/wireless/mwifiex/sdio.c
@@ -75,7 +75,9 @@
 
 	card->func = func;
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34))
 	func->card->quirks |= MMC_QUIRK_BLKSZ_FOR_BYTE_MODE;
+#endif
 
 	sdio_claim_host(func);
 	ret = sdio_enable_func(func);
