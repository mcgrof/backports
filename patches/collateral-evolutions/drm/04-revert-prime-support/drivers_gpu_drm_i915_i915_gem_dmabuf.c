--- a/drivers/gpu/drm/i915/i915_gem_dmabuf.c
+++ b/drivers/gpu/drm/i915/i915_gem_dmabuf.c
@@ -23,6 +23,7 @@
  * Authors:
  *	Dave Airlie <airlied@redhat.com>
  */
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0))
 #include <drm/drmP.h>
 #include "i915_drv.h"
 #include <linux/dma-buf.h>
@@ -307,3 +308,4 @@
 	dma_buf_detach(dma_buf, attach);
 	return ERR_PTR(ret);
 }
+#endif
