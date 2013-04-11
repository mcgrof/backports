#ifndef _BACKPORT_LINUX_ETHERDEVICE_H
#define _BACKPORT_LINUX_ETHERDEVICE_H
#include_next <linux/etherdevice.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,7,0)

/* This backports:
 *
 * commit 6d57e9078e880a3dd232d579f42ac437a8f1ef7b
 * Author: Duan Jiong <djduanjiong@gmail.com>
 * Date:   Sat Sep 8 16:32:28 2012 +0000
 * 
 *     etherdevice: introduce help function eth_zero_addr() 
 */
static inline void eth_zero_addr(u8 *addr)
{
	memset(addr, 0x00, ETH_ALEN);
}
#endif

#endif /* _BACKPORT_LINUX_ETHERDEVICE_H */
