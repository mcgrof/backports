#ifndef __BACKPORT_SKBUFF_H
#define __BACKPORT_SKBUFF_H
#include_next <linux/skbuff.h>
#include <linux/version.h>

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,28))
extern void v2_6_28_skb_add_rx_frag(struct sk_buff *skb, int i,
				    struct page *page,
				    int off, int size);

#define skb_add_rx_frag(skb, i, page, off, size, truesize) \
	v2_6_28_skb_add_rx_frag(skb, i, page, off, size)
#elif (LINUX_VERSION_CODE < KERNEL_VERSION(3,4,0))
#define skb_add_rx_frag(skb, i, page, off, size, truesize) \
	skb_add_rx_frag(skb, i, page, off, size)
#endif

#endif /* __BACKPORT_SKBUFF_H */
