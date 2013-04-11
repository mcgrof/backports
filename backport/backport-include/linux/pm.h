#ifndef __BACKPORT_PM_H
#define __BACKPORT_PM_H
#include_next <linux/pm.h>

#ifndef PM_EVENT_SLEEP
#define PM_EVENT_SLEEP  (PM_EVENT_SUSPEND)
#endif

#endif /* __BACKPORT_PM_H */
