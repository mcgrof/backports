#ifndef _COMPAT_NET_NET_NAMESPACE_H
#define _COMPAT_NET_NET_NAMESPACE_H 1

#include <linux/version.h>

#if (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,23))
#include_next <net/net_namespace.h>
#endif /* (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,23)) */

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,29)
#ifdef CONFIG_NET_NS
static inline void write_pnet(struct net **pnet, struct net *net)
{
	*pnet = net;
}

static inline struct net *read_pnet(struct net * const *pnet)
{
	return *pnet;
}

#else
#define write_pnet(pnet, net)	do { (void)(net);} while (0)
#define read_pnet(pnet)		(&init_net)
#endif
#endif /* < 2.6.29 */

#endif	/* _COMPAT_NET_NET_NAMESPACE_H */
