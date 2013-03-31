--- a/drivers/gpu/drm/nouveau/nouveau_bo.c
+++ b/drivers/gpu/drm/nouveau/nouveau_bo.c
@@ -1352,11 +1352,14 @@
 	struct drm_device *dev;
 	unsigned i;
 	int r;
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0))
 	bool slave = !!(ttm->page_flags & TTM_PAGE_FLAG_SG);
+#endif
 
 	if (ttm->state != tt_unpopulated)
 		return 0;
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0))
 	if (slave && ttm->sg) {
 		/* make userspace faulting work */
 		drm_prime_sg_to_page_addr_arrays(ttm->sg, ttm->pages,
@@ -1364,6 +1367,7 @@
 		ttm->state = tt_unbound;
 		return 0;
 	}
+#endif
 
 	drm = nouveau_bdev(ttm->bdev);
 	dev = drm->dev;
@@ -1411,10 +1415,12 @@
 	struct nouveau_drm *drm;
 	struct drm_device *dev;
 	unsigned i;
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0))
 	bool slave = !!(ttm->page_flags & TTM_PAGE_FLAG_SG);
 
 	if (slave)
 		return;
+#endif
 
 	drm = nouveau_bdev(ttm->bdev);
 	dev = drm->dev;
