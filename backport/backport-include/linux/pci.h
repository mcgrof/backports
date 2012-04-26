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

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,4,0)
/**
 * module_pci_driver() - Helper macro for registering a PCI driver
 * @__pci_driver: pci_driver struct
 *
 * Helper macro for PCI drivers which do not do anything special in module
 * init/exit. This eliminates a lot of boilerplate. Each module may only
 * use this macro once, and calling it replaces module_init() and module_exit()
 */
#define module_pci_driver(__pci_driver) \
	module_driver(__pci_driver, pci_register_driver, \
		       pci_unregister_driver)
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,7,0)
#define pcie_capability_read_word LINUX_BACKPORT(pcie_capability_read_word)
int pcie_capability_read_word(struct pci_dev *dev, int pos, u16 *val);
#define pcie_capability_read_dword LINUX_BACKPORT(pcie_capability_read_dword)
int pcie_capability_read_dword(struct pci_dev *dev, int pos, u32 *val);
#define pcie_capability_write_word LINUX_BACKPORT(pcie_capability_write_word)
int pcie_capability_write_word(struct pci_dev *dev, int pos, u16 val);
#define pcie_capability_write_dword LINUX_BACKPORT(pcie_capability_write_dword)
int pcie_capability_write_dword(struct pci_dev *dev, int pos, u32 val);
#define pcie_capability_clear_and_set_word LINUX_BACKPORT(pcie_capability_clear_and_set_word)
int pcie_capability_clear_and_set_word(struct pci_dev *dev, int pos,
				       u16 clear, u16 set);
#define pcie_capability_clear_and_set_dword LINUX_BACKPORT(pcie_capability_clear_and_set_dword)
int pcie_capability_clear_and_set_dword(struct pci_dev *dev, int pos,
					u32 clear, u32 set);

static inline int pcie_capability_set_word(struct pci_dev *dev, int pos,
					   u16 set)
{
	return pcie_capability_clear_and_set_word(dev, pos, 0, set);
}

static inline int pcie_capability_set_dword(struct pci_dev *dev, int pos,
					    u32 set)
{
	return pcie_capability_clear_and_set_dword(dev, pos, 0, set);
}

static inline int pcie_capability_clear_word(struct pci_dev *dev, int pos,
					     u16 clear)
{
	return pcie_capability_clear_and_set_word(dev, pos, clear, 0);
}

static inline int pcie_capability_clear_dword(struct pci_dev *dev, int pos,
					      u32 clear)
{
	return pcie_capability_clear_and_set_dword(dev, pos, clear, 0);
}
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
