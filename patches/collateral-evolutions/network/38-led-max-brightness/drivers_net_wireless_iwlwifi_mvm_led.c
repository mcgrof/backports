--- a/drivers/net/wireless/iwlwifi/mvm/led.c
+++ b/drivers/net/wireless/iwlwifi/mvm/led.c
@@ -108,7 +108,9 @@
 	mvm->led.name = kasprintf(GFP_KERNEL, "%s-led",
 				   wiphy_name(mvm->hw->wiphy));
 	mvm->led.brightness_set = iwl_led_brightness_set;
+#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,30)
 	mvm->led.max_brightness = 1;
+#endif
 
 	if (mode == IWL_LED_RF_STATE)
 		mvm->led.default_trigger =
