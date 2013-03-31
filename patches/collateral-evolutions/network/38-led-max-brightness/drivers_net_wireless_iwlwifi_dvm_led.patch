--- a/drivers/net/wireless/iwlwifi/dvm/led.c
+++ b/drivers/net/wireless/iwlwifi/dvm/led.c
@@ -187,7 +187,9 @@
 				   wiphy_name(priv->hw->wiphy));
 	priv->led.brightness_set = iwl_led_brightness_set;
 	priv->led.blink_set = iwl_led_blink_set;
+#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,30)
 	priv->led.max_brightness = 1;
+#endif
 
 	switch (mode) {
 	case IWL_LED_DEFAULT:
