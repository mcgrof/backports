--- a/drivers/gpu/drm/drm_bufs.c
+++ b/drivers/gpu/drm/drm_bufs.c
@@ -1541,6 +1541,20 @@
 				retcode = -EINVAL;
 				goto done;
 			}
+#if (LINUX_VERSION_CODE < KERNEL_VERSION(3,4,0))
+			down_write(&current->mm->mmap_sem);
+			virtual = do_mmap(file_priv->filp, 0, map->size,
+					  PROT_READ | PROT_WRITE,
+					  MAP_SHARED,
+					  token);
+			up_write(&current->mm->mmap_sem);
+		} else {
+			down_write(&current->mm->mmap_sem);
+			virtual = do_mmap(file_priv->filp, 0, dma->byte_count,
+					  PROT_READ | PROT_WRITE,
+					  MAP_SHARED, 0);
+			up_write(&current->mm->mmap_sem);
+#else
 			virtual = vm_mmap(file_priv->filp, 0, map->size,
 					  PROT_READ | PROT_WRITE,
 					  MAP_SHARED,
@@ -1549,6 +1563,7 @@
 			virtual = vm_mmap(file_priv->filp, 0, dma->byte_count,
 					  PROT_READ | PROT_WRITE,
 					  MAP_SHARED, 0);
+#endif
 		}
 		if (virtual > -1024UL) {
 			/* Real error */
