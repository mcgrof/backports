--- a/drivers/net/wireless/ti/wl1251/main.c
+++ b/drivers/net/wireless/ti/wl1251/main.c
@@ -24,6 +24,9 @@
 #include <linux/firmware.h>
 #include <linux/delay.h>
 #include <linux/irq.h>
+#if (LINUX_VERSION_CODE == KERNEL_VERSION(2,6,28))
+#include <linux/device.h>
+#endif
 #include <linux/crc32.h>
 #include <linux/etherdevice.h>
 #include <linux/vmalloc.h>
