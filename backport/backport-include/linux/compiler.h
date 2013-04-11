#ifndef __BACKPORT_LINUX_COMPILER_H
#define __BACKPORT_LINUX_COMPILER_H
#include_next <linux/compiler.h>

#ifndef __rcu
#define __rcu
#endif

#endif /* __BACKPORT_LINUX_COMPILER_H */
