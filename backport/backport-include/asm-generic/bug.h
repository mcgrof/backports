#ifndef __BACKPORT_ASM_GENERIC_BUG_H
#define __BACKPORT_ASM_GENERIC_BUG_H
#include_next <asm-generic/bug.h>

#ifndef __WARN
#define __WARN(foo) dump_stack()
#endif

#endif /* __BACKPORT_ASM_GENERIC_BUG_H */
