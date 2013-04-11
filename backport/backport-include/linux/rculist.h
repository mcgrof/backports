#ifndef __BACKPORT_RCULIST_H
#define __BACKPORT_RCULIST_H
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,26)
#include_next <linux/rculist.h>
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,9,0)
#include <backport/magic.h>
#define hlist_for_each_entry_rcu4(tpos, pos, head, member)		\
	for (pos = rcu_dereference_raw(hlist_first_rcu(head));		\
	     pos &&							\
		({ tpos = hlist_entry(pos, typeof(*tpos), member); 1; });\
	     pos = rcu_dereference_raw(hlist_next_rcu(pos)))

#define hlist_for_each_entry_rcu3(pos, head, member)				\
	for (pos = hlist_entry_safe (rcu_dereference_raw(hlist_first_rcu(head)),\
			typeof(*(pos)), member);				\
		pos;								\
		pos = hlist_entry_safe(rcu_dereference_raw(hlist_next_rcu(	\
			&(pos)->member)), typeof(*(pos)), member))

#undef hlist_for_each_entry_rcu
#define hlist_for_each_entry_rcu(...) \
	macro_dispatcher(hlist_for_each_entry_rcu, __VA_ARGS__)(__VA_ARGS__)
#endif /* < 3.9 */

#endif /* __BACKPORT_RCULIST_H */
