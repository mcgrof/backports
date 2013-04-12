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

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,35)
/* mask irq_set_affinity_hint as RHEL6 backports this */
#define irq_set_affinity_hint LINUX_BACKPORT(irq_set_affinity_hint)
/*
 * We cannot backport this guy as the IRQ data structure
 * was modified in the kernel itself to support this. We
 * treat the system as uni-processor in this case.
 */
static inline int irq_set_affinity_hint(unsigned int irq,
					const struct cpumask *m)
{
	return -EINVAL;
}
#endif

#endif /* __BACKPORT_LINUX_INTERRUPT_H */
