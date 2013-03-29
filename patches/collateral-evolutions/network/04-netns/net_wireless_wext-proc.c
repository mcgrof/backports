--- a/net/wireless/wext-proc.c
+++ b/net/wireless/wext-proc.c
@@ -98,7 +98,11 @@
 		return SEQ_START_TOKEN;
 
 	off = 1;
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,24))
 	for_each_netdev(net, dev)
+#else
+	for_each_netdev(net)
+#endif
 		if (off++ == *pos)
 			return dev;
 	return NULL;
