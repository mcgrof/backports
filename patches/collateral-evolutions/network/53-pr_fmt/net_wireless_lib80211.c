--- a/net/wireless/lib80211.c
+++ b/net/wireless/lib80211.c
@@ -13,8 +13,10 @@
  *
  */
 
+#undef pr_fmt
 #define pr_fmt(fmt) KBUILD_MODNAME ": " fmt
 
+#include <linux/printk.h>
 #include <linux/module.h>
 #include <linux/ctype.h>
 #include <linux/ieee80211.h>
