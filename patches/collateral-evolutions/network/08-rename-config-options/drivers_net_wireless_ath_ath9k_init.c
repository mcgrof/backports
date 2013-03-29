--- a/drivers/net/wireless/ath/ath9k/init.c
+++ b/drivers/net/wireless/ath/ath9k/init.c
@@ -809,7 +809,7 @@
 	sc->ant_rx = hw->wiphy->available_antennas_rx;
 	sc->ant_tx = hw->wiphy->available_antennas_tx;
 
-#ifdef CONFIG_ATH9K_RATE_CONTROL
+#ifdef CONFIG_COMPAT_ATH9K_RATE_CONTROL
 	hw->rate_control_algorithm = "ath9k_rate_control";
 #endif
 
