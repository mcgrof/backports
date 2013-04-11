#ifndef __BACKPORT_H
#define __BACKPORT_H
#include <backport/autoconf.h>

#ifndef __ASSEMBLY__
#define LINUX_BACKPORT(__sym) backport_ ##__sym
#include <backport/checks.h>
#endif

#endif /* __BACKPORT_H */
