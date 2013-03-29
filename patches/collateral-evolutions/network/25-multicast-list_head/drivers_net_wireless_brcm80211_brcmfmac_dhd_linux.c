--- a/drivers/net/wireless/brcm80211/brcmfmac/dhd_linux.c
+++ b/drivers/net/wireless/brcm80211/brcmfmac/dhd_linux.c
@@ -103,7 +103,11 @@
 	netdev_for_each_mc_addr(ha, ndev) {
 		if (!cnt)
 			break;
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 		memcpy(bufp, ha->addr, ETH_ALEN);
+#else
+		memcpy(bufp, ha->dmi_addr, ETH_ALEN);
+#endif
 		bufp += ETH_ALEN;
 		cnt--;
 	}
