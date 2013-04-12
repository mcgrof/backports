#ifndef __BACKPORT_MMC_SDIO_FUNC_H
#define __BACKPORT_MMC_SDIO_FUNC_H
#include <linux/version.h>
#include_next <linux/mmc/sdio_func.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,35)
#define sdio_writeb_readb(func, write_byte, addr, err_ret) sdio_readb(func, addr, err_ret)
#endif

#endif /* __BACKPORT_MMC_SDIO_FUNC_H */
