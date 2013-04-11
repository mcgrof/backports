#ifndef __BACKPORT_MEDIA_VB2_MEMOPS_H
#define __BACKPORT_MEDIA_VB2_MEMOPS_H
#include_next <media/videobuf2-memops.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,9,0) && \
    LINUX_VERSION_CODE >= KERNEL_VERSION(3,2,0)
int vb2_mmap_pfn_range(struct vm_area_struct *vma, unsigned long paddr,
				unsigned long size,
				const struct vm_operations_struct *vm_ops,
				void *priv);
#endif

#endif /* __BACKPORT_MEDIA_VB2_MEMOPS_H */
