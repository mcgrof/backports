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

#ifndef pr_warn
#define pr_warn pr_warning
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,38)
#define pr_emerg_once(fmt, ...)					\
	printk_once(KERN_EMERG pr_fmt(fmt), ##__VA_ARGS__)
#define pr_alert_once(fmt, ...)					\
	printk_once(KERN_ALERT pr_fmt(fmt), ##__VA_ARGS__)
#define pr_crit_once(fmt, ...)					\
	printk_once(KERN_CRIT pr_fmt(fmt), ##__VA_ARGS__)
#define pr_err_once(fmt, ...)					\
	printk_once(KERN_ERR pr_fmt(fmt), ##__VA_ARGS__)
#define pr_warn_once(fmt, ...)					\
	printk_once(KERN_WARNING pr_fmt(fmt), ##__VA_ARGS__)
#define pr_notice_once(fmt, ...)				\
	printk_once(KERN_NOTICE pr_fmt(fmt), ##__VA_ARGS__)
#define pr_info_once(fmt, ...)					\
	printk_once(KERN_INFO pr_fmt(fmt), ##__VA_ARGS__)
#define pr_cont_once(fmt, ...)					\
	printk_once(KERN_CONT pr_fmt(fmt), ##__VA_ARGS__)
#if defined(DEBUG)
#define pr_debug_once(fmt, ...)					\
	printk_once(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__)
#else
#define pr_debug_once(fmt, ...)					\
	no_printk(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__)
#endif
#endif

#endif	/* _COMPAT_LINUX_PRINTK_H */
