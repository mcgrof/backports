--- a/drivers/net/wireless/iwlwifi/pcie/internal.h
+++ b/drivers/net/wireless/iwlwifi/pcie/internal.h
@@ -311,6 +311,9 @@
 
 	/*protect hw register */
 	spinlock_t reg_lock;
+#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,31)
+	struct compat_threaded_irq irq_compat;
+#endif
 };
 
 /**
