--- a/drivers/bluetooth/bt3c_cs.c
+++ b/drivers/bluetooth/bt3c_cs.c
@@ -186,7 +186,11 @@
 		return;
 
 	do {
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
 		unsigned int iobase = info->p_dev->resource[0]->start;
+#else
+		unsigned int iobase = info->p_dev->io.BasePort1;
+#endif
 		register struct sk_buff *skb;
 		int len;
 
@@ -224,7 +228,11 @@
 		return;
 	}
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
 	iobase = info->p_dev->resource[0]->start;
+#else
+	iobase = info->p_dev->io.BasePort1;
+#endif
 
 	avail = bt3c_read(iobase, 0x7006);
 	//printk("bt3c_cs: receiving %d bytes\n", avail);
@@ -345,7 +353,11 @@
 		/* our irq handler is shared */
 		return IRQ_NONE;
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
 	iobase = info->p_dev->resource[0]->start;
+#else
+	iobase = info->p_dev->io.BasePort1;
+#endif
 
 	spin_lock(&(info->lock));
 
@@ -473,7 +485,11 @@
 	unsigned int iobase, size, addr, fcs, tmp;
 	int i, err = 0;
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
 	iobase = info->p_dev->resource[0]->start;
+#else
+	iobase = info->p_dev->io.BasePort1;
+#endif
 
 	/* Reset */
 	bt3c_io_write(iobase, 0x8040, 0x0404);
@@ -645,8 +661,27 @@
 	info->p_dev = link;
 	link->priv = info;
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,37))
 	link->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_VPP |
 		CONF_AUTO_SET_IO;
+#else
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
+	link->resource[0]->flags |= IO_DATA_PATH_WIDTH_8;
+	link->resource[0]->end = 8;
+#else
+	link->io.Attributes1 = IO_DATA_PATH_WIDTH_8;
+	link->io.NumPorts1= 8;
+#endif
+
+#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,35))
+	link->irq.Attributes = IRQ_TYPE_DYNAMIC_SHARING;
+
+	link->irq.Handler = bt3c_interrupt;
+#endif
+
+	link->conf.Attributes = CONF_ENABLE_IRQ;
+	link->conf.IntType = INT_MEMORY_AND_IO;
+#endif
 
 	return bt3c_config(link);
 }
@@ -657,6 +692,7 @@
 	bt3c_release(link);
 }
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,37))
 static int bt3c_check_config(struct pcmcia_device *p_dev, void *priv_data)
 {
 	int *try = priv_data;
@@ -695,6 +731,63 @@
 	}
 	return -ENODEV;
 }
+#else
+static int bt3c_check_config(struct pcmcia_device *p_dev,
+			     cistpl_cftable_entry_t *cf,
+			     cistpl_cftable_entry_t *dflt,
+			     unsigned int vcc,
+			     void *priv_data)
+{
+	unsigned long try = (unsigned long) priv_data;
+
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
+	p_dev->io_lines = (try == 0) ? 16 : cf->io.flags & CISTPL_IO_LINES_MASK;
+#endif
+
+	if (cf->vpp1.present & (1 << CISTPL_POWER_VNOM))
+		p_dev->conf.Vpp = cf->vpp1.param[CISTPL_POWER_VNOM] / 10000;
+	if ((cf->io.nwin > 0) && (cf->io.win[0].len == 8) &&
+	    (cf->io.win[0].base != 0)) {
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
+		p_dev->resource[0]->start = cf->io.win[0].base;
+		if (!pcmcia_request_io(p_dev))
+#else
+		p_dev->io.BasePort1 = cf->io.win[0].base;
+		p_dev->io.IOAddrLines = (try == 0) ? 16 :
+			cf->io.flags & CISTPL_IO_LINES_MASK;
+		if (!pcmcia_request_io(p_dev, &p_dev->io))
+#endif
+			return 0;
+	}
+	return -ENODEV;
+}
+
+static int bt3c_check_config_notpicky(struct pcmcia_device *p_dev,
+				      cistpl_cftable_entry_t *cf,
+				      cistpl_cftable_entry_t *dflt,
+				      unsigned int vcc,
+				      void *priv_data)
+{
+	static unsigned int base[5] = { 0x3f8, 0x2f8, 0x3e8, 0x2e8, 0x0 };
+	int j;
+
+	if ((cf->io.nwin > 0) && ((cf->io.flags & CISTPL_IO_LINES_MASK) <= 3)) {
+		for (j = 0; j < 5; j++) {
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
+			p_dev->resource[0]->start = base[j];
+			p_dev->io_lines = base[j] ? 16 : 3;
+			if (!pcmcia_request_io(p_dev))
+#else
+			p_dev->io.BasePort1 = base[j];
+			p_dev->io.IOAddrLines = base[j] ? 16 : 3;
+			if (!pcmcia_request_io(p_dev, &p_dev->io))
+#endif
+				return 0;
+		}
+	}
+	return -ENODEV;
+}
+#endif
 
 static int bt3c_config(struct pcmcia_device *link)
 {
@@ -718,9 +811,15 @@
 	goto failed;
 
 found_port:
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 	i = pcmcia_request_irq(link, &bt3c_interrupt);
 	if (i != 0)
 		goto failed;
+#else
+	i = pcmcia_request_irq(link, &link->irq);
+	if (i != 0)
+		link->irq.AssignedIRQ = 0;
+#endif
 
 	i = pcmcia_enable_device(link);
 	if (i != 0)
@@ -755,7 +854,13 @@
 
 static struct pcmcia_driver bt3c_driver = {
 	.owner		= THIS_MODULE,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,37))
 	.name		= "bt3c_cs",
+#else
+	.drv		= {
+		.name	= "bt3c_cs",
+	},
+#endif
 	.probe		= bt3c_probe,
 	.remove		= bt3c_detach,
 	.id_table	= bt3c_ids,
