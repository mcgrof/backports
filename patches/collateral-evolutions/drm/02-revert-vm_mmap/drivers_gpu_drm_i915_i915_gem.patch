--- a/drivers/gpu/drm/i915/i915_gem.c
+++ b/drivers/gpu/drm/i915/i915_gem.c
@@ -1294,10 +1294,17 @@
 		drm_gem_object_unreference_unlocked(obj);
 		return -EINVAL;
 	}
-
+#if (LINUX_VERSION_CODE < KERNEL_VERSION(3,4,0))
+	down_write(&current->mm->mmap_sem);
+	addr = do_mmap(obj->filp, 0, args->size,
+		       PROT_READ | PROT_WRITE, MAP_SHARED,
+		       args->offset);
+	up_write(&current->mm->mmap_sem);
+#else
 	addr = vm_mmap(obj->filp, 0, args->size,
 		       PROT_READ | PROT_WRITE, MAP_SHARED,
 		       args->offset);
+#endif
 	drm_gem_object_unreference_unlocked(obj);
 	if (IS_ERR((void *)addr))
 		return addr;
