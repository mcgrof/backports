#ifndef __BACKPORT_KERNEL_H
#define __BACKPORT_KERNEL_H
#include_next <linux/kernel.h>
#include <linux/version.h>

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,25))
/**
 * The following things are out of ./include/linux/kernel.h
 * The new iwlwifi driver is using them.
 */
#define strict_strtoul LINUX_BACKPORT(strict_strtoul)
extern int strict_strtoul(const char *, unsigned int, unsigned long *);
#define strict_strtol LINUX_BACKPORT(strict_strtol)
extern int strict_strtol(const char *, unsigned int, long *);
#endif /* (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,25)) */

#endif /* __BACKPORT_KERNEL_H */
