#ifndef __BACKPORT_USB_H
#define __BACKPORT_USB_H

#include_next <linux/usb.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,3,0)
/**
 * module_usb_driver() - Helper macro for registering a USB driver
 * @__usb_driver: usb_driver struct
 *
 * Helper macro for USB drivers which do not do anything special in module
 * init/exit. This eliminates a lot of boilerplate. Each module may only
 * use this macro once, and calling it replaces module_init() and module_exit()
 */
#define module_usb_driver(__usb_driver) \
	module_driver(__usb_driver, usb_register, \
		       usb_deregister)
#endif

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

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
#ifdef CPTCFG_BACKPORT_OPTION_USB_URB_THREAD_FIX
#define usb_scuttle_anchored_urbs LINUX_BACKPORT(usb_scuttle_anchored_urbs)
#define usb_get_from_anchor LINUX_BACKPORT(usb_get_from_anchor)
#define usb_unlink_anchored_urbs LINUX_BACKPORT(usb_unlink_anchored_urbs)

extern void usb_unlink_anchored_urbs(struct usb_anchor *anchor);
extern struct urb *usb_get_from_anchor(struct usb_anchor *anchor);
extern void usb_scuttle_anchored_urbs(struct usb_anchor *anchor);
#endif
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,35)
/* mask usb_pipe_endpoint as RHEL6 backports this */
#define usb_pipe_endpoint LINUX_BACKPORT(usb_pipe_endpoint)

static inline struct usb_host_endpoint *
usb_pipe_endpoint(struct usb_device *dev, unsigned int pipe)
{
	struct usb_host_endpoint **eps;
	eps = usb_pipein(pipe) ? dev->ep_in : dev->ep_out;
	return eps[usb_pipeendpoint(pipe)];
}
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,34)
#define usb_alloc_coherent(dev, size, mem_flags, dma) usb_buffer_alloc(dev, size, mem_flags, dma)
#define usb_free_coherent(dev, size, addr, dma) usb_buffer_free(dev, size, addr, dma)

/* USB autosuspend and autoresume */
static inline int usb_enable_autosuspend(struct usb_device *udev)
{ return 0; }
static inline int usb_disable_autosuspend(struct usb_device *udev)
{ return 0; }
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,33)
#define usb_autopm_get_interface_no_resume LINUX_BACKPORT(usb_autopm_get_interface_no_resume)
#define usb_autopm_put_interface_no_suspend LINUX_BACKPORT(usb_autopm_put_interface_no_suspend)
#ifdef CONFIG_USB_SUSPEND
extern void usb_autopm_get_interface_no_resume(struct usb_interface *intf);
extern void usb_autopm_put_interface_no_suspend(struct usb_interface *intf);
#else
static inline void usb_autopm_get_interface_no_resume(struct usb_interface *intf)
{
	atomic_inc(&intf->pm_usage_cnt);
}
static inline void usb_autopm_put_interface_no_suspend(struct usb_interface *intf)
{
	atomic_dec(&intf->pm_usage_cnt);
}
#endif /* CONFIG_USB_SUSPEND */
#endif /* < 2.6.33 */

#endif /* __BACKPORT_USB_H */
