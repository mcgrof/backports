--- a/drivers/gpu/drm/i915/intel_fb.c
+++ b/drivers/gpu/drm/i915/intel_fb.c
@@ -151,7 +151,7 @@
 	info->screen_size = size;
 
 	/* This driver doesn't need a VT switch to restore the mode on resume */
-	info->skip_vt_switch = true;
+	fb_enable_skip_vt_switch(info);
 
 	drm_fb_helper_fill_fix(info, fb->pitches[0], fb->depth);
 	drm_fb_helper_fill_var(info, &ifbdev->helper, sizes->fb_width, sizes->fb_height);
