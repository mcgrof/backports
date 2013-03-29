--- a/drivers/net/wireless/orinoco/hw.h
+++ b/drivers/net/wireless/orinoco/hw.h
@@ -22,6 +22,9 @@
 
 /* Forward declarations */
 struct orinoco_private;
+#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,35))
+struct dev_addr_list;
+#endif
 
 int determine_fw_capabilities(struct orinoco_private *priv, char *fw_name,
 			      size_t fw_name_len, u32 *hw_ver);
