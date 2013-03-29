--- a/net/bluetooth/lib.c
+++ b/net/bluetooth/lib.c
@@ -24,9 +24,11 @@
 
 /* Bluetooth kernel library. */
 
+#undef pr_fmt
 #define pr_fmt(fmt) "Bluetooth: " fmt
 
 #include <linux/export.h>
+#include <linux/printk.h>
 
 #include <net/bluetooth/bluetooth.h>
 
