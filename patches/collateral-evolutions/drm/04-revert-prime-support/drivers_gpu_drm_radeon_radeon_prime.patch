--- a/drivers/gpu/drm/radeon/radeon_prime.c
+++ b/drivers/gpu/drm/radeon/radeon_prime.c
@@ -23,6 +23,7 @@
  *
  * Authors: Alex Deucher
  */
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0))
 #include <drm/drmP.h>
 
 #include "radeon.h"
@@ -96,3 +97,4 @@
 
 	return 0;
 }
+#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0)) */
