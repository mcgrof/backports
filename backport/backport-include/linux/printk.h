#ifndef _COMPAT_LINUX_PRINTK_H
#define _COMPAT_LINUX_PRINTK_H 1

#include <linux/version.h>

#if (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,36))
#include_next <linux/printk.h>
#else
#include <linux/kernel.h>
#endif /* (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,35)) */

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,9,0)
/* backports 7a555613 */
#if defined(CONFIG_DYNAMIC_DEBUG)
#define dynamic_hex_dump(prefix_str, prefix_type, rowsize,     \
			 groupsize, buf, len, ascii)            \
do {                                                           \
	DEFINE_DYNAMIC_DEBUG_METADATA(descriptor,               \
	__builtin_constant_p(prefix_str) ? prefix_str : "hexdump");\
	if (unlikely(descriptor.flags & _DPRINTK_FLAGS_PRINT))  \
		print_hex_dump(KERN_DEBUG, prefix_str,          \
			       prefix_type, rowsize, groupsize, \
			       buf, len, ascii);                \
} while (0)
#define print_hex_dump_debug(prefix_str, prefix_type, rowsize, \
			     groupsize, buf, len, ascii)        \
	dynamic_hex_dump(prefix_str, prefix_type, rowsize,      \
			 groupsize, buf, len, ascii)
#else
#define print_hex_dump_debug(prefix_str, prefix_type, rowsize,         \
			     groupsize, buf, len, ascii)                \
	print_hex_dump(KERN_DEBUG, prefix_str, prefix_type, rowsize,    \
		       groupsize, buf, len, ascii)
#endif /* defined(CONFIG_DYNAMIC_DEBUG) */

#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(3,9,0) */

#endif	/* _COMPAT_LINUX_PRINTK_H */
