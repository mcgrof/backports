#ifndef __BACKPORT_NET_GENETLINK_H
#define __BACKPORT_NET_GENETLINK_H
#include_next <net/genetlink.h>

/* this is for patches we apply */
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,7,0)
#define genl_info_snd_portid(__genl_info) (__genl_info->snd_pid)
#else
#define genl_info_snd_portid(__genl_info) (__genl_info->snd_portid)
#endif

#endif /* __BACKPORT_NET_GENETLINK_H */
