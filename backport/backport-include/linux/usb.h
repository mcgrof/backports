#ifndef __BACKPORT_USB_H
#define __BACKPORT_USB_H

#include_next <linux/usb.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,6,0)
/**
 * Backports
 *
 * commit d81a5d1956731c453b85c141458d4ff5d6cc5366
 * Author: Gustavo Padovan <gustavo.padovan@collabora.co.uk>
 * Date:   Tue Jul 10 19:10:06 2012 -0300
 *
 * 	USB: add USB_VENDOR_AND_INTERFACE_INFO() macro
 */
#include <linux/usb.h>
#define USB_VENDOR_AND_INTERFACE_INFO(vend, cl, sc, pr) \
       .match_flags = USB_DEVICE_ID_MATCH_INT_INFO \
               | USB_DEVICE_ID_MATCH_VENDOR, \
       .idVendor = (vend), \
       .bInterfaceClass = (cl), \
       .bInterfaceSubClass = (sc), \
       .bInterfaceProtocol = (pr)
#endif

#endif /* __BACKPORT_USB_H */
