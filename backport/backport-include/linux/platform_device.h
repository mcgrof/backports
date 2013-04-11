#ifndef __BACKPORT_PLATFORM_DEVICE_H
#define __BACKPORT_PLATFORM_DEVICE_H

#include_next <linux/platform_device.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,9,0)
#define module_platform_driver_probe(__platform_driver, __platform_probe) \
static int __init __platform_driver##_init(void) \
{ \
	return platform_driver_probe(&(__platform_driver), \
				     __platform_probe);    \
} \
module_init(__platform_driver##_init); \
static void __exit __platform_driver##_exit(void) \
{ \
	platform_driver_unregister(&(__platform_driver)); \
} \
module_exit(__platform_driver##_exit);
#endif

#endif /* __BACKPORT_PLATFORM_DEVICE_H */
