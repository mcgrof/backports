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

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,38)
#if LINUX_VERSION_CODE > KERNEL_VERSION(2,6,30)
static inline void bstats_update(struct gnet_stats_basic_packed *bstats,
				 const struct sk_buff *skb)
{
	bstats->bytes += qdisc_pkt_len((struct sk_buff *) skb);
	bstats->packets += skb_is_gso(skb) ? skb_shinfo(skb)->gso_segs : 1;
}
static inline void qdisc_bstats_update(struct Qdisc *sch,
				       const struct sk_buff *skb)
{
	bstats_update(&sch->bstats, skb);
}
#else
/*
 * kernels <= 2.6.30 do not pass a const skb to qdisc_pkt_len, and
 * gnet_stats_basic_packed did not exist (see c1a8f1f1c8)
 */
static inline void bstats_update(struct gnet_stats_basic *bstats,
				 struct sk_buff *skb)
{
	bstats->bytes += qdisc_pkt_len(skb);
	bstats->packets += skb_is_gso(skb) ? skb_shinfo(skb)->gso_segs : 1;
}
static inline void qdisc_bstats_update(struct Qdisc *sch,
				       struct sk_buff *skb)
{
	bstats_update(&sch->bstats, skb);
}
#endif
#endif /* < 2.6.38 */

#endif /* __BACKPORT_NET_SCH_GENERIC_H */
