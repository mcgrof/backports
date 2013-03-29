--- a/drivers/gpu/drm/radeon/radeon_ttm.c
+++ b/drivers/gpu/drm/radeon/radeon_ttm.c
@@ -584,17 +584,21 @@
 	struct radeon_ttm_tt *gtt = (void *)ttm;
 	unsigned i;
 	int r;
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0))
 	bool slave = !!(ttm->page_flags & TTM_PAGE_FLAG_SG);
+#endif
 
 	if (ttm->state != tt_unpopulated)
 		return 0;
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0))
 	if (slave && ttm->sg) {
 		drm_prime_sg_to_page_addr_arrays(ttm->sg, ttm->pages,
 						 gtt->ttm.dma_address, ttm->num_pages);
 		ttm->state = tt_unbound;
 		return 0;
 	}
+#endif
 
 	rdev = radeon_get_rdev(ttm->bdev);
 #if __OS_HAS_AGP
@@ -638,10 +642,12 @@
 	struct radeon_device *rdev;
 	struct radeon_ttm_tt *gtt = (void *)ttm;
 	unsigned i;
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0))
 	bool slave = !!(ttm->page_flags & TTM_PAGE_FLAG_SG);
 
 	if (slave)
 		return;
+#endif
 
 	rdev = radeon_get_rdev(ttm->bdev);
 #if __OS_HAS_AGP
