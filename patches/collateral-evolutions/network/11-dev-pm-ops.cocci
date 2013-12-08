// The 2.6.29 kernel has new struct dev_pm_ops [1] which are used
// on the pci device to distinguish power management hooks for suspend
// to RAM and hibernation. Older kernels don't have these so we need
// to resort back to the good ol' suspend/resume. Fortunately the calls
// are not so different so it should be possible to resuse the same
// calls on compat code with only slight modifications.
//
// [1] http://lxr.linux.no/#linux+v2.6.29/include/linux/pm.h#L170

@ module_pci @
declarer name MODULE_DEVICE_TABLE;
identifier pci_ids;
@@

MODULE_DEVICE_TABLE(pci, pci_ids);

@ simple_dev_pm depends on module_pci @
identifier ops, pci_suspend, pci_resume;
declarer name SIMPLE_DEV_PM_OPS;
declarer name compat_pci_suspend;
declarer name compat_pci_resume;
@@

+compat_pci_suspend(pci_suspend);
+compat_pci_resume(pci_resume);
SIMPLE_DEV_PM_OPS(ops, pci_suspend, pci_resume);

@@
identifier backport_driver;
expression pm_ops;
fresh identifier backports_pci_suspend = simple_dev_pm.pci_suspend ## "_compat";
fresh identifier backports_pci_resume = simple_dev_pm.pci_resume ## "_compat";
@@

struct pci_driver backport_driver = {
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,29))
	.driver.pm  = pm_ops,
+#elif defined(CONFIG_PM_SLEEP)
+	.suspend    = backports_pci_suspend,
+	.resume     = backports_pci_resume,
+#endif
};
