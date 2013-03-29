--- a/drivers/net/wireless/brcm80211/brcmfmac/usb.c
+++ b/drivers/net/wireless/brcm80211/brcmfmac/usb.c
@@ -1498,7 +1498,9 @@
 	.resume = brcmf_usb_resume,
 	.reset_resume = brcmf_usb_reset_resume,
 	.supports_autosuspend = 1,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,5,0))
 	.disable_hub_initiated_lpm = 1,
+#endif
 };
 
 static void brcmf_release_fw(struct list_head *q)
