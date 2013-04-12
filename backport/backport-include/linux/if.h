#ifndef _BACKPORT_LINUX_IF_H
#define _BACKPORT_LINUX_IF_H
#include_next <linux/if.h>

#ifndef  IFF_TX_SKB_SHARING
#define IFF_TX_SKB_SHARING	0x10000
#endif

#endif	/* _BACKPORT_LINUX_IF_H */
