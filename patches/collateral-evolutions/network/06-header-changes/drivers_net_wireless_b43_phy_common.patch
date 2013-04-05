--- a/drivers/net/wireless/b43/phy_common.h
+++ b/drivers/net/wireless/b43/phy_common.h
@@ -3,6 +3,9 @@
 
 #include <linux/types.h>
 #include <linux/nl80211.h>
+#if (LINUX_VERSION_CODE == KERNEL_VERSION(2,6,28))
+#include <asm/atomic.h>
+#endif
 
 struct b43_wldev;
 
