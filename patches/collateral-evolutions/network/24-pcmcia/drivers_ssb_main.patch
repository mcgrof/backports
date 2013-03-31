--- a/drivers/ssb/main.c
+++ b/drivers/ssb/main.c
@@ -517,7 +517,11 @@
 			break;
 		case SSB_BUSTYPE_PCMCIA:
 #ifdef CONFIG_SSB_PCMCIAHOST
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 			sdev->irq = bus->host_pcmcia->irq;
+#else
+			sdev->irq = bus->host_pcmcia->irq.AssignedIRQ;
+#endif
 			dev->parent = &bus->host_pcmcia->dev;
 #endif
 			break;
