#include <linux/version.h>

#ifndef CPTCFG_BACKPORT_BUILD_AVERAGE
#include_next <linux/average.h>
#else
/* Exponentially weighted moving average (EWMA) */

/* For more documentation see lib/average.c */

struct ewma {
	unsigned long internal;
	unsigned long factor;
	unsigned long weight;
};

#define ewma_init LINUX_BACKPORT(ewma_init)
extern void ewma_init(struct ewma *avg, unsigned long factor,
		      unsigned long weight);

#define ewma_add LINUX_BACKPORT(ewma_add)
extern struct ewma *ewma_add(struct ewma *avg, unsigned long val);

#define ewma_read LINUX_BACKPORT(ewma_read)
/**
 * ewma_read() - Get average value
 * @avg: Average structure
 *
 * Returns the average value held in @avg.
 */
static inline unsigned long ewma_read(const struct ewma *avg)
{
	return DIV_ROUND_CLOSEST(avg->internal, avg->factor);
}
#endif /* (LINUX_VERSION_CODE > KERNEL_VERSION(2,6,37)) */
