--- a/drivers/net/wireless/brcm80211/brcmfmac/bcmsdh_sdmmc.c
+++ b/drivers/net/wireless/brcm80211/brcmfmac/bcmsdh_sdmmc.c
@@ -71,7 +71,7 @@
 brcmf_pm_resume_error(struct brcmf_sdio_dev *sdiodev)
 {
 	bool is_err = false;
-#ifdef CONFIG_PM_SLEEP
+#if defined(CONFIG_PM_SLEEP) && (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34))
 	is_err = atomic_read(&sdiodev->suspend);
 #endif
 	return is_err;
@@ -80,7 +80,7 @@
 static void
 brcmf_pm_resume_wait(struct brcmf_sdio_dev *sdiodev, wait_queue_head_t *wq)
 {
-#ifdef CONFIG_PM_SLEEP
+#if defined(CONFIG_PM_SLEEP) && (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34))
 	int retry = 0;
 	while (atomic_read(&sdiodev->suspend) && retry++ != 30)
 		wait_event_timeout(*wq, false, HZ/100);
@@ -546,7 +546,7 @@
 	brcmf_dbg(TRACE, "Exit\n");
 }
 
-#ifdef CONFIG_PM_SLEEP
+#if defined(CONFIG_PM_SLEEP) && (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34))
 static int brcmf_sdio_suspend(struct device *dev)
 {
 	mmc_pm_flag_t sdio_flags;
@@ -596,7 +596,7 @@
 	.remove = brcmf_ops_sdio_remove,
 	.name = "brcmfmac",
 	.id_table = brcmf_sdmmc_ids,
-#ifdef CONFIG_PM_SLEEP
+#if defined(CONFIG_PM_SLEEP) && (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34))
 	.drv = {
 		.pm = &brcmf_sdio_pm_ops,
 	},
