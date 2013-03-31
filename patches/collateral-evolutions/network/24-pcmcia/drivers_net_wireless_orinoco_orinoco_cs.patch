--- a/drivers/net/wireless/orinoco/orinoco_cs.c
+++ b/drivers/net/wireless/orinoco/orinoco_cs.c
@@ -78,7 +78,11 @@
 	/* We need atomic ops here, because we're not holding the lock */
 	set_bit(0, &card->hard_reset_in_progress);
 
+#if LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,27)
+	err = pcmcia_reset_card(link, NULL);
+#else
 	err = pcmcia_reset_card(link->socket);
+#endif
 	if (err)
 		return err;
 
@@ -108,6 +112,16 @@
 	card->p_dev = link;
 	link->priv = priv;
 
+#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,35))
+	/* Interrupt setup */
+	link->irq.Attributes = IRQ_TYPE_DYNAMIC_SHARING;
+	link->irq.Handler = orinoco_interrupt;
+#endif
+#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,37))
+	link->conf.Attributes = 0;
+	link->conf.IntType = INT_MEMORY_AND_IO;
+#endif
+
 	return orinoco_cs_config(link);
 }				/* orinoco_cs_attach */
 
@@ -122,6 +136,7 @@
 	free_orinocodev(priv);
 }				/* orinoco_cs_detach */
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,37))
 static int orinoco_cs_config_check(struct pcmcia_device *p_dev, void *priv_data)
 {
 	if (p_dev->config_index == 0)
@@ -129,6 +144,98 @@
 
 	return pcmcia_request_io(p_dev);
 };
+#else
+static int orinoco_cs_config_check(struct pcmcia_device *p_dev,
+				   cistpl_cftable_entry_t *cfg,
+				   cistpl_cftable_entry_t *dflt,
+				   unsigned int vcc,
+				   void *priv_data)
+{
+	if (cfg->index == 0)
+		goto next_entry;
+
+	/* Use power settings for Vcc and Vpp if present */
+	/* Note that the CIS values need to be rescaled */
+	if (cfg->vcc.present & (1 << CISTPL_POWER_VNOM)) {
+		if (vcc != cfg->vcc.param[CISTPL_POWER_VNOM] / 10000) {
+			DEBUG(2, "%s: Vcc mismatch (vcc = %d, CIS = %d)\n",
+			      __func__, vcc,
+			      cfg->vcc.param[CISTPL_POWER_VNOM] / 10000);
+			if (!ignore_cis_vcc)
+				goto next_entry;
+		}
+	} else if (dflt->vcc.present & (1 << CISTPL_POWER_VNOM)) {
+		if (vcc != dflt->vcc.param[CISTPL_POWER_VNOM] / 10000) {
+			DEBUG(2, "%s: Vcc mismatch (vcc = %d, CIS = %d)\n",
+			      __func__, vcc,
+			      dflt->vcc.param[CISTPL_POWER_VNOM] / 10000);
+			if (!ignore_cis_vcc)
+				goto next_entry;
+		}
+	}
+
+	if (cfg->vpp1.present & (1 << CISTPL_POWER_VNOM))
+		p_dev->conf.Vpp =
+			cfg->vpp1.param[CISTPL_POWER_VNOM] / 10000;
+	else if (dflt->vpp1.present & (1 << CISTPL_POWER_VNOM))
+		p_dev->conf.Vpp =
+			dflt->vpp1.param[CISTPL_POWER_VNOM] / 10000;
+
+	/* Do we need to allocate an interrupt? */
+	p_dev->conf.Attributes |= CONF_ENABLE_IRQ;
+
+	/* IO window settings */
+#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36)
+	p_dev->resource[0]->end = p_dev->resource[1]->end = 0;
+#else
+	p_dev->io.NumPorts1 = p_dev->io.NumPorts2 = 0;
+#endif
+	if ((cfg->io.nwin > 0) || (dflt->io.nwin > 0)) {
+		cistpl_io_t *io = (cfg->io.nwin) ? &cfg->io : &dflt->io;
+#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36)
+		p_dev->io_lines = io->flags & CISTPL_IO_LINES_MASK;
+		p_dev->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
+		p_dev->resource[0]->flags |=
+			pcmcia_io_cfg_data_width(io->flags);
+		p_dev->resource[0]->start = io->win[0].base;
+		p_dev->resource[0]->end = io->win[0].len;
+#else
+		p_dev->io.Attributes1 = IO_DATA_PATH_WIDTH_AUTO;
+		if (!(io->flags & CISTPL_IO_8BIT))
+			p_dev->io.Attributes1 = IO_DATA_PATH_WIDTH_16;
+		if (!(io->flags & CISTPL_IO_16BIT))
+			p_dev->io.Attributes1 = IO_DATA_PATH_WIDTH_8;
+		p_dev->io.IOAddrLines = io->flags & CISTPL_IO_LINES_MASK;
+		p_dev->io.BasePort1 = io->win[0].base;
+		p_dev->io.NumPorts1 = io->win[0].len;
+#endif
+		if (io->nwin > 1) {
+#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36)
+			p_dev->resource[1]->flags = p_dev->resource[0]->flags;
+			p_dev->resource[1]->start = io->win[1].base;
+			p_dev->resource[1]->end = io->win[1].len;
+#else
+			p_dev->io.Attributes2 = p_dev->io.Attributes1;
+			p_dev->io.BasePort2 = io->win[1].base;
+			p_dev->io.NumPorts2 = io->win[1].len;
+#endif
+		}
+
+		/* This reserves IO space but doesn't actually enable it */
+#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36)
+		if (pcmcia_request_io(p_dev) != 0)
+#else
+		if (pcmcia_request_io(p_dev, &p_dev->io) != 0)
+#endif
+			goto next_entry;
+	}
+	return 0;
+
+next_entry:
+	pcmcia_disable_device(p_dev);
+	return -ENODEV;
+};
+#endif
 
 static int
 orinoco_cs_config(struct pcmcia_device *link)
@@ -138,10 +245,12 @@
 	int ret;
 	void __iomem *mem;
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,37))
 	link->config_flags |= CONF_AUTO_SET_VPP | CONF_AUTO_CHECK_VCC |
 		CONF_AUTO_SET_IO | CONF_ENABLE_IRQ;
 	if (ignore_cis_vcc)
 		link->config_flags &= ~CONF_AUTO_CHECK_VCC;
+#endif
 	ret = pcmcia_loop_config(link, orinoco_cs_config_check, NULL);
 	if (ret) {
 		if (!ignore_cis_vcc)
@@ -151,8 +260,12 @@
 		goto failed;
 	}
 
+#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36)
 	mem = ioport_map(link->resource[0]->start,
 			resource_size(link->resource[0]));
+#else
+	mem = ioport_map(link->io.BasePort1, link->io.NumPorts1);
+#endif
 	if (!mem)
 		goto failed;
 
@@ -161,7 +274,11 @@
 	 * called. */
 	hermes_struct_init(hw, mem, HERMES_16BIT_REGSPACING);
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
 	ret = pcmcia_request_irq(link, orinoco_interrupt);
+#else
+	ret = pcmcia_request_irq(link, &link->irq);
+#endif
 	if (ret)
 		goto failed;
 
@@ -176,8 +293,16 @@
 	}
 
 	/* Register an interface with the stack */
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
 	if (orinoco_if_add(priv, link->resource[0]->start,
 			   link->irq, NULL) != 0) {
+#elif (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,35))
+	if (orinoco_if_add(priv, link->io.BasePort1,
+			   link->irq, NULL) != 0) {
+#else
+	if (orinoco_if_add(priv, link->io.BasePort1,
+			   link->irq.AssignedIRQ, NULL) != 0) {
+#endif
 		printk(KERN_ERR PFX "orinoco_if_add() failed\n");
 		goto failed;
 	}
@@ -331,7 +456,13 @@
 
 static struct pcmcia_driver orinoco_driver = {
 	.owner		= THIS_MODULE,
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,37))
 	.name		= DRIVER_NAME,
+#else
+	.drv		= {
+		.name	= DRIVER_NAME,
+	},
+#endif
 	.probe		= orinoco_cs_probe,
 	.remove		= orinoco_cs_detach,
 	.id_table       = orinoco_cs_ids,
