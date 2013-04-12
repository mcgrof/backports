#ifndef __BACKPORT_HID_H
#define __BACKPORT_HID_H
#include_next <linux/hid.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,8,0)
#define hid_ignore LINUX_BACKPORT(hid_ignore)
extern bool hid_ignore(struct hid_device *);
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,1,0)
#define HID_TYPE_USBNONE 2
#endif

#endif /* __BACKPORT_HID_H */
