--- a/drivers/gpu/drm/radeon/radeon_ttm.c
+++ b/drivers/gpu/drm/radeon/radeon_ttm.c
@@ -603,11 +603,13 @@
 	}
 #endif
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,3,0))
 #ifdef CONFIG_SWIOTLB
 	if (swiotlb_nr_tbl()) {
 		return ttm_dma_populate(&gtt->ttm, rdev->dev);
 	}
 #endif
+#endif
 
 	r = ttm_pool_populate(ttm);
 	if (r) {
@@ -649,12 +651,14 @@
 	}
 #endif
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,3,0))
 #ifdef CONFIG_SWIOTLB
 	if (swiotlb_nr_tbl()) {
 		ttm_dma_unpopulate(&gtt->ttm, rdev->dev);
 		return;
 	}
 #endif
+#endif
 
 	for (i = 0; i < ttm->num_pages; i++) {
 		if (gtt->ttm.dma_address[i]) {
@@ -877,6 +881,7 @@
 	radeon_mem_types_list[i].show = &ttm_page_alloc_debugfs;
 	radeon_mem_types_list[i].driver_features = 0;
 	radeon_mem_types_list[i++].data = NULL;
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,3,0))
 #ifdef CONFIG_SWIOTLB
 	if (swiotlb_nr_tbl()) {
 		sprintf(radeon_mem_types_names[i], "ttm_dma_page_pool");
@@ -886,6 +891,7 @@
 		radeon_mem_types_list[i++].data = NULL;
 	}
 #endif
+#endif
 	return radeon_debugfs_add_files(rdev, radeon_mem_types_list, i);
 
 #endif
