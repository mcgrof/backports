--- a/drivers/net/usb/cdc_ether.c
+++ b/drivers/net/usb/cdc_ether.c
@@ -33,7 +33,7 @@
 #include <linux/usb/usbnet.h>
 
 
-#if defined(CONFIG_USB_NET_RNDIS_HOST) || defined(CONFIG_USB_NET_RNDIS_HOST_MODULE)
+#if defined(CONFIG_USB_NET_COMPAT_RNDIS_HOST) || defined(CONFIG_USB_NET_COMPAT_RNDIS_HOST_MODULE)
 
 static int is_rndis(struct usb_interface_descriptor *desc)
 {
