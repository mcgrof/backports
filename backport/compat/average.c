/*
 * Copyright 2010    Hauke Mehrtens <hauke@hauke-m.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Compatibility file for Linux wireless for kernels 2.6.38.
 */

#include <linux/average.h>
#include <linux/module.h>
#include <linux/bug.h>
#include <linux/log2.h>

/**
 * ewma_init() - Initialize EWMA parameters
 * @avg: Average structure
 * @factor: Factor to use for the scaled up internal value. The maximum value
 *	of averages can be ULONG_MAX/(factor*weight). For performance reasons
 *	factor has to be a power of 2.
 * @weight: Exponential weight, or decay rate. This defines how fast the
 *	influence of older values decreases. For performance reasons weight has
 *	to be a power of 2.
 *
 * Initialize the EWMA parameters for a given struct ewma @avg.
 */
void ewma_init(struct ewma *avg, unsigned long factor, unsigned long weight)
{
	WARN_ON(!is_power_of_2(weight) || !is_power_of_2(factor));

	avg->weight = ilog2(weight);
	avg->factor = ilog2(factor);
	avg->internal = 0;
}
EXPORT_SYMBOL_GPL(ewma_init);

/**
 * ewma_add() - Exponentially weighted moving average (EWMA)
 * @avg: Average structure
 * @val: Current value
 *
 * Add a sample to the average.
 */
struct ewma *ewma_add(struct ewma *avg, unsigned long val)
{
	avg->internal = avg->internal  ?
		(((avg->internal << avg->weight) - avg->internal) +
			(val << avg->factor)) >> avg->weight :
		(val << avg->factor);
	return avg;
}
EXPORT_SYMBOL_GPL(ewma_add);

