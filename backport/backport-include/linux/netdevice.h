#ifndef __BACKPORT_NETDEVICE_H
#define __BACKPORT_NETDEVICE_H
#include_next <linux/netdevice.h>
#include <linux/netdev_features.h>
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

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,3,0)
/*
 * BQL was added as of v3.3 but some Linux distributions
 * have backported BQL to their v3.2 kernels or older. To
 * address this we assume that they also enabled CONFIG_BQL
 * and test for that here and simply avoid adding the static
 * inlines if it was defined
 */
#ifndef CONFIG_BQL
#if (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,26))
static inline void netdev_tx_sent_queue(struct netdev_queue *dev_queue,
					unsigned int bytes)
{
}
#endif

static inline void netdev_sent_queue(struct net_device *dev, unsigned int bytes)
{
}

#if (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,26))
static inline void netdev_tx_completed_queue(struct netdev_queue *dev_queue,
					     unsigned pkts, unsigned bytes)
{
}
#endif

static inline void netdev_completed_queue(struct net_device *dev,
					  unsigned pkts, unsigned bytes)
{
}

#if (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,26))
static inline void netdev_tx_reset_queue(struct netdev_queue *q)
{
}
#endif

static inline void netdev_reset_queue(struct net_device *dev_queue)
{
}
#endif /* CONFIG_BQL */
#endif /* < 3.3 */

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,0,0)
/*
 * since commit 1c5cae815d19ffe02bdfda1260949ef2b1806171
 * "net: call dev_alloc_name from register_netdevice" dev_alloc_name is
 * called automatically. This is not implemented in older kernel
 * versions so it will result in device wrong names.
 */
static inline int register_netdevice_name(struct net_device *dev)
{
	int err;

	if (strchr(dev->name, '%')) {
		err = dev_alloc_name(dev, dev->name);
		if (err < 0)
			return err;
	}

	return register_netdevice(dev);
}

#define register_netdevice(dev) register_netdevice_name(dev)
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,38)
#define alloc_netdev_mqs(sizeof_priv, name, setup, txqs, rxqs) \
	alloc_netdev_mq(sizeof_priv, name, setup, \
			max_t(unsigned int, txqs, rxqs))
#endif

#endif /* __BACKPORT_NETDEVICE_H */
