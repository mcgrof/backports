#ifndef __BACKPORT_NET_SCH_GENERIC_H
#define __BACKPORT_NET_SCH_GENERIC_H
#include_next <net/sch_generic.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,3,0)
#if !((LINUX_VERSION_CODE >= KERNEL_VERSION(3,2,9) && LINUX_VERSION_CODE < KERNEL_VERSION(3,3,0)) || (LINUX_VERSION_CODE >= KERNEL_VERSION(3,0,23) && LINUX_VERSION_CODE < KERNEL_VERSION(3,1,0)))
#if LINUX_VERSION_CODE > KERNEL_VERSION(2,6,37)
/* mask qdisc_cb_private_validate as RHEL6 backports this */
#define qdisc_cb_private_validate(a,b) compat_qdisc_cb_private_validate(a,b)
static inline void qdisc_cb_private_validate(const struct sk_buff *skb, int sz)
{
	BUILD_BUG_ON(sizeof(skb->cb) < sizeof(struct qdisc_skb_cb) + sz);
}
#else
/* mask qdisc_cb_private_validate as RHEL6 backports this */
#define qdisc_cb_private_validate(a,b) compat_qdisc_cb_private_validate(a,b)
static inline void qdisc_cb_private_validate(const struct sk_buff *skb, int sz)
{
	/* XXX ? */
}
#endif
#endif
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(3,3,0) */

#endif /* __BACKPORT_NET_SCH_GENERIC_H */
