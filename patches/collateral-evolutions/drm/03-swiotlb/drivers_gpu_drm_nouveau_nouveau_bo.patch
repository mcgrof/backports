--- a/drivers/gpu/drm/nouveau/nouveau_bo.c
+++ b/drivers/gpu/drm/nouveau/nouveau_bo.c
@@ -1374,11 +1374,13 @@
 	}
 #endif
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,3,0))
 #ifdef CONFIG_SWIOTLB
 	if (swiotlb_nr_tbl()) {
 		return ttm_dma_populate((void *)ttm, dev->dev);
 	}
 #endif
+#endif
 
 	r = ttm_pool_populate(ttm);
 	if (r) {
@@ -1424,12 +1426,14 @@
 	}
 #endif
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,3,0))
 #ifdef CONFIG_SWIOTLB
 	if (swiotlb_nr_tbl()) {
 		ttm_dma_unpopulate((void *)ttm, dev->dev);
 		return;
 	}
 #endif
+#endif
 
 	for (i = 0; i < ttm->num_pages; i++) {
 		if (ttm_dma->dma_address[i]) {
