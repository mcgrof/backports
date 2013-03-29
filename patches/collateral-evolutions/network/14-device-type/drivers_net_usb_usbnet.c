--- a/drivers/net/usb/usbnet.c
+++ b/drivers/net/usb/usbnet.c
@@ -1363,13 +1363,17 @@
 
 // precondition: never called in_interrupt
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,32))
 static struct device_type wlan_type = {
 	.name	= "wlan",
 };
+#endif
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,32))
 static struct device_type wwan_type = {
 	.name	= "wwan",
 };
+#endif
 
 int
 usbnet_probe (struct usb_interface *udev, const struct usb_device_id *prod)
