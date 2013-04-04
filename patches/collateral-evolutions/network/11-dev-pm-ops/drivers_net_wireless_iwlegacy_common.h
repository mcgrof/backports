--- a/drivers/net/wireless/iwlegacy/common.h
+++ b/drivers/net/wireless/iwlegacy/common.h
@@ -1833,7 +1833,14 @@ __le32 il_add_beacon_time(struct il_priv
 			  u32 beacon_interval);
 
 #ifdef CONFIG_PM
+#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,29))
+int il_pci_suspend_compat(struct pci_dev *pdev, pm_message_t state);
+int il_pci_resume_compat(struct pci_dev *pdev);
+#elif (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,32))
+extern struct dev_pm_ops il_pm_ops;
+#else
 extern const struct dev_pm_ops il_pm_ops;
+#endif
 
 #define IL_LEGACY_PM_OPS	(&il_pm_ops)
 
