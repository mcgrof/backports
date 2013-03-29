--- a/drivers/bcma/host_pci.c
+++ b/drivers/bcma/host_pci.c
@@ -257,6 +257,9 @@
 	return bcma_bus_resume(bus);
 }
 
+compat_pci_suspend(bcma_host_pci_suspend)
+compat_pci_resume(bcma_host_pci_resume)
+
 static SIMPLE_DEV_PM_OPS(bcma_pm_ops, bcma_host_pci_suspend,
 			 bcma_host_pci_resume);
 #define BCMA_PM_OPS	(&bcma_pm_ops)
@@ -285,7 +288,12 @@
 	.id_table = bcma_pci_bridge_tbl,
 	.probe = bcma_host_pci_probe,
 	.remove = bcma_host_pci_remove,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,29))
 	.driver.pm = BCMA_PM_OPS,
+#elif defined(CONFIG_PM_SLEEP)
+	.suspend = bcma_host_pci_suspend_compat,
+	.resume = bcma_host_pci_resume_compat,
+#endif
 };
 
 int __init bcma_host_pci_init(void)
