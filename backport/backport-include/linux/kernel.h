#ifndef __BACKPORT_KERNEL_H
#define __BACKPORT_KERNEL_H
#include_next <linux/kernel.h>
#include <linux/version.h>

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,25))
/**
 * The following things are out of ./include/linux/kernel.h
 * The new iwlwifi driver is using them.
 */
#define strict_strtoul LINUX_BACKPORT(strict_strtoul)
extern int strict_strtoul(const char *, unsigned int, unsigned long *);
#define strict_strtol LINUX_BACKPORT(strict_strtol)
extern int strict_strtol(const char *, unsigned int, long *);
#endif /* (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,25)) */

/*
 * This backports:
 *
 *   From a3860c1c5dd1137db23d7786d284939c5761d517 Mon Sep 17 00:00:00 2001
 *   From: Xi Wang <xi.wang@gmail.com>
 *   Date: Thu, 31 May 2012 16:26:04 -0700
 *   Subject: [PATCH] introduce SIZE_MAX
 */
#ifndef SIZE_MAX
#define SIZE_MAX    (~(size_t)0)
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,26)
extern const char hex_asc[];
#endif

#ifndef hex_asc_hi
#define hex_asc_hi(x)	hex_asc[((x) & 0xf0) >> 4]
#endif
#ifndef hex_asc_lo
#define hex_asc_lo(x)	hex_asc[((x) & 0x0f)]
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,2,0)
static inline char *hex_byte_pack(char *buf, u8 byte)
{
	*buf++ = hex_asc_hi(byte);
	*buf++ = hex_asc_lo(byte);
	return buf;
}
#endif

#endif /* __BACKPORT_KERNEL_H */
