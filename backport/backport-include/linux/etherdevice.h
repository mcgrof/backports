#ifndef _BACKPORT_LINUX_ETHERDEVICE_H
#define _BACKPORT_LINUX_ETHERDEVICE_H
#include_next <linux/etherdevice.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,6,0)
#include <linux/random.h>
/**
 * eth_broadcast_addr - Assign broadcast address
 * @addr: Pointer to a six-byte array containing the Ethernet address
 *
 * Assign the broadcast address to the given address array.
 */
static inline void eth_broadcast_addr(u8 *addr)
{
	memset(addr, 0xff, ETH_ALEN);
}

/**
 * eth_random_addr - Generate software assigned random Ethernet address
 * @addr: Pointer to a six-byte array containing the Ethernet address
 *
 * Generate a random Ethernet address (MAC) that is not multicast
 * and has the local assigned bit set.
 */
static inline void eth_random_addr(u8 *addr)
{
	get_random_bytes(addr, ETH_ALEN);
	addr[0] &= 0xfe;        /* clear multicast bit */
	addr[0] |= 0x02;        /* set local assignment bit (IEEE802) */
}
#endif

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
