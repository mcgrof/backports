--- a/drivers/gpu/drm/drm_crtc_helper.c
+++ b/drivers/gpu/drm/drm_crtc_helper.c
@@ -152,7 +152,7 @@
 		goto prune;
 	}
 
-#ifdef CONFIG_DRM_LOAD_EDID_FIRMWARE
+#ifdef CONFIG_COMPAT_DRM_LOAD_EDID_FIRMWARE
 	count = drm_load_edid_firmware(connector);
 	if (count == 0)
 #endif
