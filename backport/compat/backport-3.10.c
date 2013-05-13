/*
 * Copyright (c) 2013  Luis R. Rodriguez <mcgrof@do-not-panic.com>
 *
 * Linux backport symbols for kernels 3.10.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,6,0))
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/debugfs.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/async.h>
#include <linux/err.h>
#include <linux/mutex.h>
#include <linux/suspend.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/of.h>
#include <linux/regmap.h>
#include <linux/regulator/of_regulator.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/module.h>

/**
 * regulator_map_voltage_ascend - map_voltage() for ascendant voltage list
 *
 * @rdev: Regulator to operate on
 * @min_uV: Lower bound for voltage
 * @max_uV: Upper bound for voltage
 *
 * Drivers that have ascendant voltage list can use this as their
 * map_voltage() operation.
 */
int regulator_map_voltage_ascend(struct regulator_dev *rdev,
				 int min_uV, int max_uV)
{
	int i, ret;

	for (i = 0; i < rdev->desc->n_voltages; i++) {
		ret = rdev->desc->ops->list_voltage(rdev, i);
		if (ret < 0)
			continue;

		if (ret > max_uV)
			break;

		if (ret >= min_uV && ret <= max_uV)
			return i;
	}

	return -EINVAL;
}
EXPORT_SYMBOL_GPL(regulator_map_voltage_ascend);

#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(3,6,0)) */
