#ifndef __BACKPORT_TYPES_H
#define __BACKPORT_TYPES_H
#include_next <linux/types.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,25)
#if defined(CONFIG_X86) || defined(CONFIG_X86_64)

#if defined(CONFIG_64BIT) || defined(CONFIG_X86_PAE) || defined(CONFIG_PHYS_64BIT)
typedef u64 phys_addr_t;
#else
typedef u32 phys_addr_t;
#endif

#endif /* x86 */
#elif LINUX_VERSION_CODE < KERNEL_VERSION(2,6,28) /* < 2.6.25 */

#if defined(CONFIG_X86) || defined(CONFIG_X86_64) || defined(CONFIG_PPC)
/*
 * CONFIG_PHYS_ADDR_T_64BIT was added as new to all architectures
 * as of 2.6.28 but x86 and ppc had it already.
 */
#else
#if defined(CONFIG_64BIT) || defined(CONFIG_X86_PAE) || defned(CONFIG_PPC64) || defined(CONFIG_PHYS_64BIT)
#define CONFIG_PHYS_ADDR_T_64BIT 1
typedef u64 phys_addr_t;
#else
typedef u32 phys_addr_t;
#endif

#endif /* non x86 and ppc */

#endif /* < 2.6.28 */

#endif /* __BACKPORT_TYPES_H */
