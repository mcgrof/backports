--- a/drivers/net/wireless/orinoco/hermes.h
+++ b/drivers/net/wireless/orinoco/hermes.h
@@ -393,7 +393,7 @@
 			 u16 id, u16 offset);
 	int (*bap_pwrite)(struct hermes *hw, int bap, const void *buf,
 			  int len, u16 id, u16 offset);
-	int (*read_pda)(struct hermes *hw, __le16 *pda,
+	int (*read_pda_h)(struct hermes *hw, __le16 *pda,
 			u32 pda_addr, u16 pda_len);
 	int (*program_init)(struct hermes *hw, u32 entry_point);
 	int (*program_end)(struct hermes *hw);
