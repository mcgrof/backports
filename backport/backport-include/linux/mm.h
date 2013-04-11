#ifndef __BACKPORT_MM_H
#define __BACKPORT_MM_H
#include_next <linux/mm.h>

#ifndef VM_DONTDUMP
#define VM_DONTDUMP    VM_NODUMP
#endif

#endif /* __BACKPORT_MM_H */
