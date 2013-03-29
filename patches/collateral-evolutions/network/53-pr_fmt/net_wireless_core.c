--- a/net/wireless/core.c
+++ b/net/wireless/core.c
@@ -4,8 +4,10 @@
  * Copyright 2006-2010		Johannes Berg <johannes@sipsolutions.net>
  */
 
+#undef pr_fmt
 #define pr_fmt(fmt) KBUILD_MODNAME ": " fmt
 
+#include <linux/printk.h>
 #include <linux/if.h>
 #include <linux/module.h>
 #include <linux/err.h>
