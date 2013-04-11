#ifndef _COMPAT_LINUX_FS_H
#define _COMPAT_LINUX_FS_H
#include_next <linux/fs.h>
#include <linux/version.h>
/*
 * some versions don't have this and thus don't
 * include it from the original fs.h
 */
#include <linux/uidgid.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,9,0)
/**
 * backport of:
 *
 * commit 496ad9aa8ef448058e36ca7a787c61f2e63f0f54
 * Author: Al Viro <viro@zeniv.linux.org.uk>
 * Date:   Wed Jan 23 17:07:38 2013 -0500
 *
 *     new helper: file_inode(file)
 */
static inline struct inode *file_inode(struct file *f)
{
	return f->f_path.dentry->d_inode;
}
#endif

#endif	/* _COMPAT_LINUX_FS_H */
