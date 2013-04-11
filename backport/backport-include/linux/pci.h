#ifndef _BACKPORT_LINUX_PCI_H
#define _BACKPORT_LINUX_PCI_H
#include_next <linux/pci.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,25)
/* Backports b718989da7 */
#define pci_enable_device_mem LINUX_BACKPORT(pci_enable_device_mem)
int __must_check pci_enable_device_mem(struct pci_dev *dev);

#define DEFINE_PCI_DEVICE_TABLE(_table) \
	const struct pci_device_id _table[] __devinitdata
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,10,0)
/*
 * DRM requires this, but we can't really backport it well
 */
static inline void __iomem *pci_platform_rom(struct pci_dev *pdev, size_t *size)
{
	printk(KERN_WARNING "compat: not providing pci_platform_rom!\n");
	return NULL;
}
#endif

#endif /* _BACKPORT_LINUX_PCI_H */
