--- a/drivers/bluetooth/hci_ldisc.c
+++ b/drivers/bluetooth/hci_ldisc.c
@@ -421,7 +421,10 @@
 	hdev->close = hci_uart_close;
 	hdev->flush = hci_uart_flush;
 	hdev->send  = hci_uart_send_frame;
+
+#if (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,36))
 	SET_HCIDEV_DEV(hdev, hu->tty->dev);
+#endif
 
 	if (test_bit(HCI_UART_RAW_DEVICE, &hu->hdev_flags))
 		set_bit(HCI_QUIRK_RAW_DEVICE, &hdev->quirks);
