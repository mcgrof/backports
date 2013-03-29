--- a/net/mac80211/rate.c
+++ b/net/mac80211/rate.c
@@ -24,7 +24,7 @@
 static LIST_HEAD(rate_ctrl_algs);
 static DEFINE_MUTEX(rate_ctrl_mutex);
 
-static char *ieee80211_default_rc_algo = CONFIG_MAC80211_RC_DEFAULT;
+static char *ieee80211_default_rc_algo = CONFIG_COMPAT_MAC80211_RC_DEFAULT;
 module_param(ieee80211_default_rc_algo, charp, 0644);
 MODULE_PARM_DESC(ieee80211_default_rc_algo,
 		 "Default rate control algorithm for mac80211 to use");
@@ -120,8 +120,8 @@
 		ops = ieee80211_try_rate_control_ops_get(ieee80211_default_rc_algo);
 
 	/* try built-in one if specific alg requested but not found */
-	if (!ops && strlen(CONFIG_MAC80211_RC_DEFAULT))
-		ops = ieee80211_try_rate_control_ops_get(CONFIG_MAC80211_RC_DEFAULT);
+	if (!ops && strlen(CONFIG_COMPAT_MAC80211_RC_DEFAULT))
+		ops = ieee80211_try_rate_control_ops_get(CONFIG_COMPAT_MAC80211_RC_DEFAULT);
 	kparam_unblock_sysfs_write(ieee80211_default_rc_algo);
 
 	return ops;
