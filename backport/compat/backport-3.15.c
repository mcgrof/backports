/*
 * Copyright (c) 2014  Hauke Mehrtens <hauke@hauke-m.de>
 *
 * Backport functionality introduced in Linux 3.15.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/device.h>

/**
 * devm_kstrdup - Allocate resource managed space and
 *                copy an existing string into that.
 * @dev: Device to allocate memory for
 * @s: the string to duplicate
 * @gfp: the GFP mask used in the devm_kmalloc() call when
 *       allocating memory
 * RETURNS:
 * Pointer to allocated string on success, NULL on failure.
 */
char *devm_kstrdup(struct device *dev, const char *s, gfp_t gfp)
{
	size_t size;
	char *buf;

	if (!s)
		return NULL;

	size = strlen(s) + 1;
	buf = devm_kmalloc(dev, size, gfp);
	if (buf)
		memcpy(buf, s, size);
	return buf;
}
EXPORT_SYMBOL_GPL(devm_kstrdup);
