--- a/drivers/net/wireless/libertas/if_sdio.c
+++ b/drivers/net/wireless/libertas/if_sdio.c
@@ -877,6 +877,7 @@
 	if (ret)
 		goto release;
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,32))
 	/* For 1-bit transfers to the 8686 model, we need to enable the
 	 * interrupt flag in the CCCR register. Set the MMC_QUIRK_LENIENT_FN0
 	 * bit to allow access to non-vendor registers. */
@@ -895,6 +896,7 @@
 		if (ret)
 			goto disable;
 	}
+#endif
 
 	card->ioport = sdio_readb(func, IF_SDIO_IOPORT, &ret);
 	if (ret)
