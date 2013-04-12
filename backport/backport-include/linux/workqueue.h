#ifndef __BACKPORT_LINUX_WORKQUEUE_H
#define __BACKPORT_LINUX_WORKQUEUE_H
#include_next <linux/workqueue.h>
#include <linux/version.h>

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3,7,0))
#define mod_delayed_work LINUX_BACKPORT(mod_delayed_work)
bool mod_delayed_work(struct workqueue_struct *wq, struct delayed_work *dwork,
		      unsigned long delay);
#endif

#ifndef create_freezable_workqueue
/* note freez_a_ble -> freez_ea_able */
#define create_freezable_workqueue create_freezeable_workqueue
#endif

#ifndef alloc_ordered_workqueue
#define alloc_ordered_workqueue(name, flags) create_singlethread_workqueue(name)
#endif

#endif /* __BACKPORT_LINUX_WORKQUEUE_H */
