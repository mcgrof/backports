#ifndef __BACKPORT_LINUX_RTNETLINK_H
#define __BACKPORT_LINUX_RTNETLINK_H
#include_next <linux/rtnetlink.h>

#ifndef rtnl_dereference
#define rtnl_dereference(p)                                     \
        rcu_dereference_protected(p, lockdep_rtnl_is_held())
#endif

#endif /* __BACKPORT_LINUX_RTNETLINK_H */
