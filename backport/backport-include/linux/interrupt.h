#ifndef __BACKPORT_LINUX_INTERRUPT_H
#define __BACKPORT_LINUX_INTERRUPT_H
#include_next <linux/interrupt.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39)
static inline int irq_set_irq_wake(unsigned int irq, unsigned int on)
{
	return set_irq_wake(irq, on);
}
#endif

#endif /* __BACKPORT_LINUX_INTERRUPT_H */
