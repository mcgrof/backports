--- a/drivers/net/wireless/iwlwifi/dvm/led.c
+++ b/drivers/net/wireless/iwlwifi/dvm/led.c
@@ -162,6 +162,7 @@
 	iwl_led_cmd(priv, on, 0);
 }
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,25))
 static int iwl_led_blink_set(struct led_classdev *led_cdev,
 			     unsigned long *delay_on,
 			     unsigned long *delay_off)
@@ -170,6 +171,7 @@
 
 	return iwl_led_cmd(priv, *delay_on, *delay_off);
 }
+#endif
 
 void iwl_leds_init(struct iwl_priv *priv)
 {
@@ -186,7 +188,9 @@
 	priv->led.name = kasprintf(GFP_KERNEL, "%s-led",
 				   wiphy_name(priv->hw->wiphy));
 	priv->led.brightness_set = iwl_led_brightness_set;
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,25))
 	priv->led.blink_set = iwl_led_blink_set;
+#endif
 #if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,30)
 	priv->led.max_brightness = 1;
 #endif
