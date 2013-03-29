--- a/drivers/net/wireless/iwlwifi/pcie/drv.c
+++ b/drivers/net/wireless/iwlwifi/pcie/drv.c
@@ -347,6 +347,9 @@
 	return iwl_trans_resume(iwl_trans);
 }
 
+compat_pci_suspend(iwl_pci_suspend)
+compat_pci_resume(iwl_pci_resume)
+
 static SIMPLE_DEV_PM_OPS(iwl_dev_pm_ops, iwl_pci_suspend, iwl_pci_resume);
 
 #define IWL_PM_OPS	(&iwl_dev_pm_ops)
@@ -362,7 +365,12 @@
 	.id_table = iwl_hw_card_ids,
 	.probe = iwl_pci_probe,
 	.remove = iwl_pci_remove,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,29))
 	.driver.pm = IWL_PM_OPS,
+#elif defined(CONFIG_PM_SLEEP)
+	.suspend = iwl_pci_suspend_compat,
+	.resume = iwl_pci_resume_compat,
+#endif
 };
 
 int __must_check iwl_pci_register_driver(void)
