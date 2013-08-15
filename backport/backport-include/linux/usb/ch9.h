#ifndef __BACKPORT__LINUX_USB_CH9_H
#define __BACKPORT__LINUX_USB_CH9_H

#include_next <linux/usb/ch9.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,2,0)
#include <linux/types.h>    /* __u8 etc */
#include <asm/byteorder.h>  /* le16_to_cpu */

/**
 * usb_endpoint_maxp - get endpoint's max packet size
 * @epd: endpoint to be checked
 *
 * Returns @epd's max packet
 */
static inline int usb_endpoint_maxp(const struct usb_endpoint_descriptor *epd)
{
	return __le16_to_cpu(epd->wMaxPacketSize);
}
#endif /* < 3.2 */

#endif /* __BACKPORT__LINUX_USB_CH9_H */
