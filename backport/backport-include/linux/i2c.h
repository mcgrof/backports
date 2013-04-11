#ifndef __BACKPORT_LINUX_I2C_H
#define __BACKPORT_LINUX_I2C_H
#include_next <linux/i2c.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,2,0) && \
    LINUX_VERSION_CODE < KERNEL_VERSION(3,6,0)
#include <linux/i2c.h>
/* Unlocked flavor */
#define __i2c_transfer LINUX_BACKPORT(__i2c_transfer)
extern int __i2c_transfer(struct i2c_adapter *adap, struct i2c_msg *msgs,
			  int num);
#endif

#endif /* __BACKPORT_LINUX_I2C_H */
