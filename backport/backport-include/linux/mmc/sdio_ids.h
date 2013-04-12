#ifndef __BACKPORT_MMC_SDIO_IDS_H
#define __BACKPORT_MMC_SDIO_IDS_H
#include <linux/version.h>
#include_next <linux/mmc/sdio_ids.h>

#ifndef SDIO_CLASS_BT_AMP
#define SDIO_CLASS_BT_AMP	0x09	/* Type-A Bluetooth AMP interface */
#endif

#endif /* __BACKPORT_MMC_SDIO_IDS_H */
