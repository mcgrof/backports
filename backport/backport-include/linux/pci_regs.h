#ifndef __BACKPORT_UAPI_PCI_REGS_H
#define __BACKPORT_UAPI_PCI_REGS_H
#include_next <linux/pci_regs.h>

#ifndef PCI_EXP_LNKCTL_ASPM_L0S
#define  PCI_EXP_LNKCTL_ASPM_L0S  0x01 /* L0s Enable */
#endif

#ifndef PCI_EXP_LNKCTL_ASPM_L1
#define  PCI_EXP_LNKCTL_ASPM_L1   0x02 /* L1 Enable */
#endif

/* This backports:
 *
 * commit 130f1b8f35f14d27c43da755f3c9226318c17f57
 * Author: Bjorn Helgaas <bhelgaas@google.com>
 * Date:   Wed Dec 26 10:39:23 2012 -0700
 *
 *     PCI: Add PCIe Link Capability link speed and width names
 */
#ifndef PCI_EXP_LNKCAP_SLS_2_5GB
#define  PCI_EXP_LNKCAP_SLS_2_5GB 0x1	/* LNKCAP2 SLS Vector bit 0 (2.5GT/s) */
#endif

#ifndef PCI_EXP_LNKCAP_SLS_5_0GB
#define  PCI_EXP_LNKCAP_SLS_5_0GB 0x2	/* LNKCAP2 SLS Vector bit 1 (5.0GT/s) */
#endif

#ifndef PCI_EXP_LNKSTA2
#define PCI_EXP_LNKSTA2			50      /* Link Status 2 */
#endif

#endif /* __BACKPORT_UAPI_PCI_REGS_H */
