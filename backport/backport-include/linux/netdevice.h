#ifndef __BACKPORT_NETDEVICE_H
#define __BACKPORT_NETDEVICE_H
#include_next <linux/netdevice.h>
#include <linux/version.h>

/* older kernels don't include this here, we need it */
#include <linux/ethtool.h>

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3,8,0))
#define netdev_set_default_ethtool_ops LINUX_BACKPORT(netdev_set_default_ethtool_ops)
extern void netdev_set_default_ethtool_ops(struct net_device *dev,
					   const struct ethtool_ops *ops);
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,25)
#define __dev_addr_sync LINUX_BACKPORT(__dev_addr_sync)
extern int __dev_addr_sync(struct dev_addr_list **to, int *to_count, struct dev_addr_list **from, int *from_count);
#define __dev_addr_unsync LINUX_BACKPORT(__dev_addr_unsync)
extern void __dev_addr_unsync(struct dev_addr_list **to, int *to_count, struct dev_addr_list **from, int *from_count);
#endif

#endif /* __BACKPORT_NETDEVICE_H */
