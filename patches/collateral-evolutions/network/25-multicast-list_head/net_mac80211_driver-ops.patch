--- a/net/mac80211/driver-ops.h
+++ b/net/mac80211/driver-ops.h
@@ -227,20 +227,35 @@ static inline void drv_bss_info_changed(
 }
 
 static inline u64 drv_prepare_multicast(struct ieee80211_local *local,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 					struct netdev_hw_addr_list *mc_list)
+#else
+					int mc_count,
+					struct dev_addr_list *mc_list)
+#endif
 {
 	u64 ret = 0;
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 	trace_drv_prepare_multicast(local, mc_list->count);
+#else
+	trace_drv_prepare_multicast(local, mc_count);
+#endif
 
 	if (local->ops->prepare_multicast)
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 		ret = local->ops->prepare_multicast(&local->hw, mc_list);
+#else
+		ret = local->ops->prepare_multicast(&local->hw, mc_count,
+						    mc_list);
+#endif
 
 	trace_drv_return_u64(local, ret);
 
 	return ret;
 }
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 static inline void drv_set_multicast_list(struct ieee80211_local *local,
 					  struct ieee80211_sub_if_data *sdata,
 					  struct netdev_hw_addr_list *mc_list)
@@ -256,6 +271,23 @@ static inline void drv_set_multicast_lis
 					       allmulti, mc_list);
 	trace_drv_return_void(local);
 }
+#else
+static inline void drv_set_multicast_list(struct ieee80211_local *local,
+					  struct ieee80211_sub_if_data *sdata,
+					  int mc_count, struct dev_addr_list *ha)
+{
+	bool allmulti = sdata->flags & IEEE80211_SDATA_ALLMULTI;
+
+	trace_drv_set_multicast_list(local, sdata, mc_count);
+
+	check_sdata_in_driver(sdata);
+
+	if (local->ops->set_multicast_list)
+		local->ops->set_multicast_list(&local->hw, &sdata->vif,
+					       allmulti, mc_count, ha);
+	trace_drv_return_void(local);
+}
+#endif
 
 static inline void drv_configure_filter(struct ieee80211_local *local,
 					unsigned int changed_flags,
