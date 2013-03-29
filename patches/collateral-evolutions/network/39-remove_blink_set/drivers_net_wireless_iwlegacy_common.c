--- a/drivers/net/wireless/iwlegacy/common.c
+++ b/drivers/net/wireless/iwlegacy/common.c
@@ -540,6 +540,7 @@
 	il_led_cmd(il, on, 0);
 }
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,25))
 static int
 il_led_blink_set(struct led_classdev *led_cdev, unsigned long *delay_on,
 		 unsigned long *delay_off)
@@ -548,6 +549,7 @@
 
 	return il_led_cmd(il, *delay_on, *delay_off);
 }
+#endif
 
 void
 il_leds_init(struct il_priv *il)
@@ -561,7 +563,9 @@
 	il->led.name =
 	    kasprintf(GFP_KERNEL, "%s-led", wiphy_name(il->hw->wiphy));
 	il->led.brightness_set = il_led_brightness_set;
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,25))
 	il->led.blink_set = il_led_blink_set;
+#endif
 #if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,30)
 	il->led.max_brightness = 1;
 #endif
