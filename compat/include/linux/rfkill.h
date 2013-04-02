#ifndef __COMPAT_RFKILL_H
#define __COMPAT_RFKILL_H

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,31))
#include_next <linux/rfkill.h>
#else
#include <linux/rfkill_backport.h>
#endif

#endif
