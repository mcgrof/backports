--- a/drivers/net/wireless/orinoco/fw.c
+++ b/drivers/net/wireless/orinoco/fw.c
@@ -123,7 +123,7 @@
 	dev_dbg(dev, "Attempting to download firmware %s\n", firmware);
 
 	/* Read current plug data */
-	err = hw->ops->read_pda(hw, pda, fw->pda_addr, fw->pda_size);
+	err = hw->ops->read_pda_h(hw, pda, fw->pda_addr, fw->pda_size);
 	dev_dbg(dev, "Read PDA returned %d\n", err);
 	if (err)
 		goto free;
@@ -225,7 +225,7 @@
 		if (!pda)
 			return -ENOMEM;
 
-		ret = hw->ops->read_pda(hw, pda, fw->pda_addr, fw->pda_size);
+		ret = hw->ops->read_pda_h(hw, pda, fw->pda_addr, fw->pda_size);
 		if (ret)
 			goto free;
 	}
