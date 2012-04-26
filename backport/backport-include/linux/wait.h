#ifndef __BACKPORT_LINUX_WAIT_H
#define __BACKPORT_LINUX_WAIT_H
#include_next <linux/wait.h>

/* This backports:
 *
 * commit 63b2001169e75cd71e917ec953fdab572e3f944a
 * Author: Thomas Gleixner <tglx@linutronix.de>
 * Date:   Thu Dec 1 00:04:00 2011 +0100
 *
 * 	sched/wait: Add __wake_up_all_locked() API
 */

#ifndef wake_up_all_locked
extern void compat_wake_up_locked(wait_queue_head_t *q, unsigned int mode, int nr);
#define wake_up_all_locked(x)	compat_wake_up_locked((x), TASK_NORMAL, 0)
#endif

#endif /* __BACKPORT_LINUX_WAIT_H */
