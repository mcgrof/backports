--- a/drivers/net/wireless/libertas/if_spi.c
+++ b/drivers/net/wireless/libertas/if_spi.c
@@ -1249,6 +1249,7 @@
 	return 0;
 }
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,29))
 static int if_spi_suspend(struct device *dev)
 {
 	struct spi_device *spi = to_spi_device(dev);
@@ -1282,6 +1283,7 @@
 	.suspend	= if_spi_suspend,
 	.resume		= if_spi_resume,
 };
+#endif
 
 static struct spi_driver libertas_spi_driver = {
 	.probe	= if_spi_probe,
@@ -1289,7 +1291,9 @@
 	.driver = {
 		.name	= "libertas_spi",
 		.owner	= THIS_MODULE,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,29))
 		.pm	= &if_spi_pm_ops,
+#endif
 	},
 };
 
