--- a/drivers/net/wireless/ath/ath6kl/sdio.c
+++ b/drivers/net/wireless/ath/ath6kl/sdio.c
@@ -817,6 +817,7 @@
 	return ret;
 }
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34))
 static int ath6kl_set_sdio_pm_caps(struct ath6kl *ar)
 {
 	struct ath6kl_sdio *ar_sdio = ath6kl_sdio_priv(ar);
@@ -950,6 +951,17 @@
 
 	return 0;
 }
+#else
+static int ath6kl_sdio_suspend(struct ath6kl *ar, struct cfg80211_wowlan *wow)
+{
+	return 0;
+}
+
+static int ath6kl_sdio_resume(struct ath6kl *ar)
+{
+	return 0;
+}
+#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34)) */
 
 /* set the window address register (using 4-byte register access ). */
 static int ath6kl_set_addrwin_reg(struct ath6kl *ar, u32 reg_addr, u32 addr)
@@ -1263,7 +1275,7 @@
 	.stop = ath6kl_sdio_stop,
 };
 
-#ifdef CONFIG_PM_SLEEP
+#if defined(CONFIG_PM_SLEEP) && (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34))
 
 /*
  * Empty handlers so that mmc subsystem doesn't remove us entirely during
@@ -1413,7 +1425,9 @@
 	.id_table = ath6kl_sdio_devices,
 	.probe = ath6kl_sdio_probe,
 	.remove = ath6kl_sdio_remove,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,34))
 	.drv.pm = ATH6KL_SDIO_PM_OPS,
+#endif
 };
 
 static int __init ath6kl_sdio_init(void)
