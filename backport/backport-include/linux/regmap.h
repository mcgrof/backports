#ifndef __BACKPORT_LINUX_REGMAP_H
#define __BACKPORT_LINUX_REGMAP_H
#include_next <linux/regmap.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,5,0) && \
    LINUX_VERSION_CODE >= KERNEL_VERSION(3,2,0)
#define dev_get_regmap LINUX_BACKPORT(dev_get_regmap)
static inline
struct regmap *dev_get_regmap(struct device *dev, const char *name)
{
	return NULL;
}
#endif

#endif /* __BACKPORT_LINUX_REGMAP_H */
