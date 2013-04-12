#ifndef __BACKPORT_ASM_GENERIC_BUG_H
#define __BACKPORT_ASM_GENERIC_BUG_H
#include_next <asm-generic/bug.h>

#ifndef __WARN
#define __WARN(foo) dump_stack()
#endif

#ifndef WARN_ONCE
#define WARN_ONCE(condition, format...) ({                      \
	static int __warned;                                    \
	int __ret_warn_once = !!(condition);                    \
								\
	if (unlikely(__ret_warn_once))                          \
		if (WARN(!__warned, format))                    \
			__warned = 1;                           \
	unlikely(__ret_warn_once);                              \
})
#endif

#endif /* __BACKPORT_ASM_GENERIC_BUG_H */
