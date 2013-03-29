--- a/drivers/net/wireless/iwlegacy/common.h
+++ b/drivers/net/wireless/iwlegacy/common.h
@@ -1348,7 +1348,7 @@
 
 		} _3945;
 #endif
-#if defined(CONFIG_IWL4965) || defined(CONFIG_IWL4965_MODULE)
+#if defined(CONFIG_COMPAT_IWL4965) || defined(CONFIG_COMPAT_IWL4965_MODULE)
 		struct {
 			struct il_rx_phy_res last_phy_res;
 			bool last_phy_res_valid;
