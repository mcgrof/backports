--- a/net/wireless/nl80211.c
+++ b/net/wireless/nl80211.c
@@ -1600,6 +1600,7 @@
 						 &cb->args[2],
 						 &cb->args[3]);
 			if (ret < 0) {
+#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,1,0)
 				/*
 				 * If sending the wiphy data didn't fit (ENOBUFS
 				 * or EMSGSIZE returned), this SKB is still
@@ -1620,6 +1621,7 @@
 					mutex_unlock(&cfg80211_mutex);
 					return 1;
 				}
+#endif
 				idx--;
 				break;
 			}
