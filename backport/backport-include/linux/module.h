#ifndef __BACKPORT_LINUX_MODULE_H
#define __BACKPORT_LINUX_MODULE_H
#include_next <linux/module.h>

/*
 * The define overwriting module_init is based on the original module_init
 * which looks like this:
 * #define module_init(initfn)					\
 *	static inline initcall_t __inittest(void)		\
 *	{ return initfn; }					\
 *	int init_module(void) __attribute__((alias(#initfn)));
 *
 * To the call to the initfn we added the symbol dependency on compat
 * to make sure that compat.ko gets loaded for any compat modules.
 */
extern void backport_dependency_symbol(void);

#ifdef BACKPORTS_GIT_TRACKED
#define BACKPORT_MOD_VERSIONS MODULE_VERSION(BACKPORTS_GIT_TRACKED);
#else
#define BACKPORT_MOD_VERSIONS						\
	MODULE_VERSION("backported from " BACKPORTED_KERNEL_NAME	\
		       " (" BACKPORTED_KERNEL_VERSION ")"		\
		       " using backports " BACKPORTS_VERSION);
#endif

#undef module_init
#define module_init(initfn)						\
	static int __init __init_backport(void)				\
	{								\
		backport_dependency_symbol();				\
		return initfn();					\
	}								\
	int init_module(void) __attribute__((alias("__init_backport")));\
	BACKPORT_MOD_VERSIONS

#endif /* __BACKPORT_LINUX_MODULE_H */
