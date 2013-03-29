--- a/drivers/net/ethernet/broadcom/b44.c
+++ b/drivers/net/ethernet/broadcom/b44.c
@@ -1693,7 +1693,11 @@
 	netdev_for_each_mc_addr(ha, dev) {
 		if (i == num_ents)
 			break;
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 		__b44_cam_write(bp, ha->addr, i++ + 1);
+#else
+		__b44_cam_write(bp, ha->dmi_addr, i++ + 1);
+#endif
 	}
 	return i+1;
 }
