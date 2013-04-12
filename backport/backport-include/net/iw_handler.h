#ifndef __BACKPORT_NET_IW_HANDLER_H
#define __BACKPORT_NET_IW_HANDLER_H
#include_next <net/iw_handler.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,32)
#define wireless_send_event(a, b, c, d) wireless_send_event(a, b, c, (char * ) d)
#endif

#endif /* __BACKPORT_NET_IW_HANDLER_H */
