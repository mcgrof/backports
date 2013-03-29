--- a/drivers/net/wireless/ath/ath5k/pci.c
+++ b/drivers/net/wireless/ath/ath5k/pci.c
@@ -326,6 +326,9 @@
 	return 0;
 }
 
+compat_pci_suspend(ath5k_pci_suspend)
+compat_pci_resume(ath5k_pci_resume)
+
 static SIMPLE_DEV_PM_OPS(ath5k_pm_ops, ath5k_pci_suspend, ath5k_pci_resume);
 #define ATH5K_PM_OPS	(&ath5k_pm_ops)
 #else
@@ -337,7 +340,12 @@
 	.id_table	= ath5k_pci_id_table,
 	.probe		= ath5k_pci_probe,
 	.remove		= ath5k_pci_remove,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,29))
 	.driver.pm	= ATH5K_PM_OPS,
+#elif defined(CONFIG_PM_SLEEP)
+	.suspend        = ath5k_pci_suspend_compat,
+	.resume         = ath5k_pci_resume_compat,
+#endif
 };
 
 module_pci_driver(ath5k_pci_driver);
