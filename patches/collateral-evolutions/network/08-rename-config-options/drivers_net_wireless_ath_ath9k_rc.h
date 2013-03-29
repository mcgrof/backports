--- a/drivers/net/wireless/ath/ath9k/rc.h
+++ b/drivers/net/wireless/ath/ath9k/rc.h
@@ -231,7 +231,7 @@
 }
 #endif
 
-#ifdef CONFIG_ATH9K_RATE_CONTROL
+#ifdef CONFIG_COMPAT_ATH9K_RATE_CONTROL
 int ath_rate_control_register(void);
 void ath_rate_control_unregister(void);
 #else
