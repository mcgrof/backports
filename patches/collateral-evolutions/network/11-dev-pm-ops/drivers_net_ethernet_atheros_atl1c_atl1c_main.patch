--- a/drivers/net/ethernet/atheros/atl1c/atl1c_main.c
+++ b/drivers/net/ethernet/atheros/atl1c/atl1c_main.c
@@ -2743,6 +2743,9 @@
 	.resume = atl1c_io_resume,
 };
 
+compat_pci_suspend(atl1c_suspend)
+compat_pci_resume(atl1c_resume)
+
 static SIMPLE_DEV_PM_OPS(atl1c_pm_ops, atl1c_suspend, atl1c_resume);
 
 static struct pci_driver atl1c_driver = {
@@ -2752,7 +2755,12 @@
 	.remove   = atl1c_remove,
 	.shutdown = atl1c_shutdown,
 	.err_handler = &atl1c_err_handler,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,29))
 	.driver.pm = &atl1c_pm_ops,
+#elif defined(CONFIG_PM_SLEEP)
+	.suspend        = atl1c_suspend_compat,
+	.resume         = atl1c_resume_compat,
+#endif
 };
 
 /**
