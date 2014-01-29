#ifndef __BACKPORT_PTP_CLOCK_KERNEL_H
#define __BACKPORT_PTP_CLOCK_KERNEL_H

#include <linux/version.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,0,0)
#include_next <linux/ptp_clock_kernel.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,7,0)
#define ptp_clock_register(info,parent) ptp_clock_register(info)
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(3,7,0) */

#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(3,0,0) */

#endif /* __BACKPORT_PTP_CLOCK_KERNEL_H */
