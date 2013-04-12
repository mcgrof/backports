#ifndef __BACKPORT_NETDEV_FEATURES_H
#define __BACKPORT_NETDEV_FEATURES_H

#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,3,0)
#include <linux/netdevice.h>
#include <linux/types.h>

typedef u32 netdev_features_t;
#else
#include_next <linux/netdev_features.h>
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(3,3,0) */

#if !defined(NETIF_F_RXCSUM)
#define NETIF_F_RXCSUM 0
#endif

#endif /* __BACKPORT_NETDEV_FEATURES_H */
