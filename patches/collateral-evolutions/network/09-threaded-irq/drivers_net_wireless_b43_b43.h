--- a/drivers/net/wireless/b43/b43.h
+++ b/drivers/net/wireless/b43/b43.h
@@ -872,6 +872,9 @@
 	unsigned int tx_count;
 	unsigned int rx_count;
 #endif
+#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,31)
+	struct compat_threaded_irq irq_compat;
+#endif
 };
 
 /* Data structure for the WLAN parts (802.11 cores) of the b43 chip. */
