#ifndef __BACKPORT_LINUX_HDMI_H
#define __BACKPORT_LINUX_HDMI_H
#include_next <linux/hdmi.h>

#include <linux/version.h>

/* on kernel < 3.9 hdmi gets backported */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,9,0)
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,12,0)

struct hdmi_any_infoframe {
	enum hdmi_infoframe_type type;
	unsigned char version;
	unsigned char length;
};

union hdmi_infoframe {
	struct hdmi_any_infoframe any;
	struct hdmi_avi_infoframe avi;
	struct hdmi_spd_infoframe spd;
	struct hdmi_vendor_infoframe vendor;
	struct hdmi_audio_infoframe audio;
};

#define hdmi_infoframe_pack LINUX_BACKPORT(hdmi_infoframe_pack)
ssize_t
hdmi_infoframe_pack(union hdmi_infoframe *frame, void *buffer, size_t size);
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(3,12,0)*/ 
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(3,9,0) */

#ifndef HDMI_INFOFRAME_SIZE
#define HDMI_INFOFRAME_SIZE(type)	\
	(HDMI_INFOFRAME_HEADER_SIZE + HDMI_ ## type ## _INFOFRAME_SIZE)
#endif

#endif /* __BACKPORT_LINUX_HDMI_H */
