--- a/drivers/gpu/drm/drm_fb_helper.c
+++ b/drivers/gpu/drm/drm_fb_helper.c
@@ -27,9 +27,11 @@
  *      Dave Airlie <airlied@linux.ie>
  *      Jesse Barnes <jesse.barnes@intel.com>
  */
+#undef pr_fmt
 #define pr_fmt(fmt) KBUILD_MODNAME ": " fmt
 
 #include <linux/kernel.h>
+#include <linux/printk.h>
 #include <linux/sysrq.h>
 #include <linux/slab.h>
 #include <linux/fb.h>
