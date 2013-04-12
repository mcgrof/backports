#ifndef __BACKPORT_LINUX_ERR_H
#define __BACKPORT_LINUX_ERR_H
#include_next <linux/err.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39)
static inline int __must_check PTR_RET(const void *ptr)
{
	if (IS_ERR(ptr))
		return PTR_ERR(ptr);
	else
		return 0;
}
#endif

#endif /* __BACKPORT_LINUX_ERR_H */
