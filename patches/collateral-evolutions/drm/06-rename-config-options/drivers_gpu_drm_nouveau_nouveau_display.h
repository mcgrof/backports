--- a/drivers/gpu/drm/nouveau/nouveau_display.h
+++ b/drivers/gpu/drm/nouveau/nouveau_display.h
@@ -73,7 +73,7 @@
 
 void nouveau_hdmi_mode_set(struct drm_encoder *, struct drm_display_mode *);
 
-#ifdef CONFIG_DRM_NOUVEAU_BACKLIGHT
+#ifdef CONFIG_COMPAT_DRM_NOUVEAU_BACKLIGHT
 extern int nouveau_backlight_init(struct drm_device *);
 extern void nouveau_backlight_exit(struct drm_device *);
 #else
