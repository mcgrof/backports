--- a/net/bluetooth/bnep/core.c
+++ b/net/bluetooth/bnep/core.c
@@ -526,9 +526,11 @@
 	return conn ? &conn->dev : NULL;
 }
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,32))
 static struct device_type bnep_type = {
 	.name	= "bluetooth",
 };
+#endif
 
 int bnep_add_connection(struct bnep_connadd_req *req, struct socket *sock)
 {
