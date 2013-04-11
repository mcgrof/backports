#ifndef __BACKPORT_LINUX_FIRMWARE_H
#define __BACKPORT_LINUX_FIRMWARE_H
#include_next <linux/firmware.h>
#include <linux/version.h>

#if defined(CPTCFG_BACKPORT_BUILD_FW_LOADER_MODULE)
#define request_firmware_nowait LINUX_BACKPORT(request_firmware_nowait)
#define request_firmware LINUX_BACKPORT(request_firmware)
#define release_firmware LINUX_BACKPORT(release_firmware)

int request_firmware(const struct firmware **fw, const char *name,
		     struct device *device);
int request_firmware_nowait(
	struct module *module, int uevent,
	const char *name, struct device *device, gfp_t gfp, void *context,
	void (*cont)(const struct firmware *fw, void *context));

void release_firmware(const struct firmware *fw);
#endif

#endif /* __BACKPORT_LINUX_FIRMWARE_H */
