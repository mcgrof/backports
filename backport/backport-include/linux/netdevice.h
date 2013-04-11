#ifndef __BACKPORT_NETDEVICE_H
#define __BACKPORT_NETDEVICE_H
#include_next <linux/netdevice.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,25)
#define __dev_addr_sync LINUX_BACKPORT(__dev_addr_sync)
extern int __dev_addr_sync(struct dev_addr_list **to, int *to_count, struct dev_addr_list **from, int *from_count);
#define __dev_addr_unsync LINUX_BACKPORT(__dev_addr_unsync)
extern void __dev_addr_unsync(struct dev_addr_list **to, int *to_count, struct dev_addr_list **from, int *from_count);
#endif

#endif /* __BACKPORT_NETDEVICE_H */
