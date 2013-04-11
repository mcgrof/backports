#ifndef __BACKPORT_DEVICE_H
#define __BACKPORT_DEVICE_H
#include <linux/export.h>
#include_next <linux/device.h>

#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,25)
#define dev_emerg(dev, format, arg...)          \
	dev_printk(KERN_EMERG , dev , format , ## arg)
#define dev_alert(dev, format, arg...)          \
	dev_printk(KERN_ALERT , dev , format , ## arg)
#define dev_crit(dev, format, arg...)           \
	dev_printk(KERN_CRIT , dev , format , ## arg)
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,9,0)
#define devm_ioremap_resource LINUX_BACKPORT(devm_ioremap_resource)
void __iomem *devm_ioremap_resource(struct device *dev, struct resource *res);
#endif

#endif /* __BACKPORT_DEVICE_H */
