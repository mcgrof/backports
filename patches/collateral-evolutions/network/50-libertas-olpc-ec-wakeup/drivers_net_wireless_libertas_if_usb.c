--- a/drivers/net/wireless/libertas/if_usb.c
+++ b/drivers/net/wireless/libertas/if_usb.c
@@ -962,6 +962,7 @@
 		goto out;
 	}
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,1,0))
 #ifdef CONFIG_OLPC
 	if (machine_is_olpc()) {
 		if (priv->wol_criteria == EHS_REMOVE_WAKEUP)
@@ -970,6 +971,7 @@
 			olpc_ec_wakeup_set(EC_SCI_SRC_WLAN);
 	}
 #endif
+#endif
 
 	ret = lbs_suspend(priv);
 	if (ret)
