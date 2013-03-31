--- a/drivers/gpu/drm/nouveau/nouveau_prime.c
+++ b/drivers/gpu/drm/nouveau/nouveau_prime.c
@@ -22,6 +22,8 @@
  * Authors: Dave Airlie
  */
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0))
+
 #include <drm/drmP.h>
 
 #include "nouveau_drm.h"
@@ -93,3 +95,4 @@
 
 	return 0;
 }
+#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0)) */
