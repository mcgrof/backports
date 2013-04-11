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

/**
 * Backports
 *
 * commit cdcac9cd7741af2c2b9255cbf060f772596907bb
 * Author: Dave Airlie <airlied@redhat.com>
 * Date:   Wed Jun 27 08:35:52 2012 +0100
 *
 * 	pci_regs: define LNKSTA2 pcie cap + bits.
 *
 * 	We need these for detecting the max link speed for drm drivers.
 *
 * 	Acked-by: Bjorn Helgaas <bhelgass@google.com>
 * 	Signed-off-by: Dave Airlie <airlied@redhat.com>
 */
#ifndef PCI_EXP_LNKCAP2
#define  PCI_EXP_LNKCAP2 		44	/* Link Capability 2 */
#endif

#ifndef PCI_EXP_LNKCAP2_SLS_2_5GB
#define  PCI_EXP_LNKCAP2_SLS_2_5GB 	0x01	/* Current Link Speed 2.5GT/s */
#endif

#ifndef PCI_EXP_LNKCAP2_SLS_5_0GB
#define  PCI_EXP_LNKCAP2_SLS_5_0GB 	0x02	/* Current Link Speed 5.0GT/s */
#endif

#ifndef PCI_EXP_LNKCAP2_SLS_8_0GB
#define  PCI_EXP_LNKCAP2_SLS_8_0GB 	0x04	/* Current Link Speed 8.0GT/s */
#endif

#ifndef PCI_EXP_LNKCAP2_CROSSLINK
#define  PCI_EXP_LNKCAP2_CROSSLINK 	0x100 /* Crosslink supported */
#endif

#endif /* __BACKPORT_UAPI_PCI_REGS_H */
