--- a/drivers/net/wireless/rtlwifi/rtl8723ae/sw.c
+++ b/drivers/net/wireless/rtlwifi/rtl8723ae/sw.c
@@ -367,6 +367,9 @@
 MODULE_PARM_DESC(fwlps, "Set to 1 to use FW control power save (default 1)\n");
 MODULE_PARM_DESC(debug, "Set debug level (0-5) (default 0)");
 
+compat_pci_suspend(rtl_pci_suspend);
+compat_pci_resume(rtl_pci_resume);
+
 static SIMPLE_DEV_PM_OPS(rtlwifi_pm_ops, rtl_pci_suspend, rtl_pci_resume);
 
 static struct pci_driver rtl8723ae_driver = {
@@ -374,7 +377,12 @@
 	.id_table = rtl8723ae_pci_ids,
 	.probe = rtl_pci_probe,
 	.remove = rtl_pci_disconnect,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,29))
 	.driver.pm = &rtlwifi_pm_ops,
+#elif defined(CONFIG_PM_SLEEP)
+	.suspend    = rtl_pci_suspend_compat,
+	.resume     = rtl_pci_resume_compat,
+#endif
 };
 
 module_pci_driver(rtl8723ae_driver);
