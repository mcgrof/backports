#ifndef __BACKPORT_PROC_FS_H
#define __BACKPORT_PROC_FS_H
#include_next <linux/proc_fs.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,10,0)
/*
 * backport of:
 * procfs: new helper - PDE_DATA(inode)
 */
static inline void *PDE_DATA(const struct inode *inode)
{
	return PROC_I(inode)->pde->data;
}
#endif

#endif /* __BACKPORT_PROC_FS_H */
