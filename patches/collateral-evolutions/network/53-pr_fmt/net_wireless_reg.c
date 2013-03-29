--- a/net/wireless/reg.c
+++ b/net/wireless/reg.c
@@ -42,9 +42,11 @@
  *
  */
 
+#undef pr_fmt
 #define pr_fmt(fmt) KBUILD_MODNAME ": " fmt
 
 #include <linux/kernel.h>
+#include <linux/printk.h>
 #include <linux/export.h>
 #include <linux/slab.h>
 #include <linux/list.h>
