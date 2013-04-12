#ifndef __BACKPORT_LINUX_LOCKDEP_H
#define __BACKPORT_LINUX_LOCKDEP_H
#include_next <linux/lockdep.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,38)
/* Backport of:
 *
 * commit e159489baa717dbae70f9903770a6a4990865887
 * Author: Tejun Heo <tj@kernel.org>
 * Date:   Sun Jan 9 23:32:15 2011 +0100
 *
 *     workqueue: relax lockdep annotation on flush_work()
 */
#ifdef CONFIG_DEBUG_LOCK_ALLOC
# ifdef CONFIG_PROVE_LOCKING
#  define lock_map_acquire_read(l)	lock_acquire(l, 0, 0, 2, 2, NULL, _THIS_IP_)
# else
#  define lock_map_acquire_read(l)	lock_acquire(l, 0, 0, 2, 1, NULL, _THIS_IP_)
# endif
#else
# define lock_map_acquire_read(l)		do { } while (0)
#endif

#endif /* < 2.6.38 */

#ifndef lockdep_assert_held
#define lockdep_assert_held(l)			do { } while (0)
#endif

#endif /* __BACKPORT_LINUX_LOCKDEP_H */
