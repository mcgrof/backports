--- a/drivers/bcma/bcma_private.h
+++ b/drivers/bcma/bcma_private.h
@@ -1,10 +1,10 @@
 #ifndef LINUX_BCMA_PRIVATE_H_
 #define LINUX_BCMA_PRIVATE_H_
 
-#ifndef pr_fmt
+#undef pr_fmt
 #define pr_fmt(fmt)		KBUILD_MODNAME ": " fmt
-#endif
 
+#include <linux/printk.h>
 #include <linux/bcma/bcma.h>
 #include <linux/delay.h>
 
