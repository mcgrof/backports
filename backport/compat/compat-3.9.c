/*
 * Copyright (c) 2013  Luis R. Rodriguez <mcgrof@do-not-panic.com>
 *
 * Compatibility file for Linux wireless for kernels 3.9.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/scatterlist.h>
#include <linux/device.h>
#include <linux/err.h>

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,2,0))
#include <media/videobuf2-memops.h>
/**
 * vb2_mmap_pfn_range() - map physical pages to userspace
 * @vma:	virtual memory region for the mapping
 * @paddr:	starting physical address of the memory to be mapped
 * @size:	size of the memory to be mapped
 * @vm_ops:	vm operations to be assigned to the created area
 * @priv:	private data to be associated with the area
 *
 * Returns 0 on success.
 */
int vb2_mmap_pfn_range(struct vm_area_struct *vma, unsigned long paddr,
				unsigned long size,
				const struct vm_operations_struct *vm_ops,
				void *priv)
{
	int ret;

	size = min_t(unsigned long, vma->vm_end - vma->vm_start, size);

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	ret = remap_pfn_range(vma, vma->vm_start, paddr >> PAGE_SHIFT,
				size, vma->vm_page_prot);
	if (ret) {
		printk(KERN_ERR "Remapping memory failed, error: %d\n", ret);
		return ret;
	}

	vma->vm_flags		|= VM_DONTEXPAND | VM_DONTDUMP;
	vma->vm_private_data	= priv;
	vma->vm_ops		= vm_ops;

	vma->vm_ops->open(vma);

	pr_debug("%s: mapped paddr 0x%08lx at 0x%08lx, size %ld\n",
			__func__, paddr, vma->vm_start, size);

	return 0;
}
EXPORT_SYMBOL_GPL(vb2_mmap_pfn_range);
#endif


#ifdef __sg_page_iter_next

void __sg_page_iter_start(struct sg_page_iter *piter,
			  struct scatterlist *sglist, unsigned int nents,
			  unsigned long pgoffset)
{
	piter->__pg_advance = 0;
	piter->__nents = nents;

	piter->page = NULL;
	piter->sg = sglist;
	piter->sg_pgoffset = pgoffset;
}
EXPORT_SYMBOL_GPL(__sg_page_iter_start);

static int sg_page_count(struct scatterlist *sg)
{
	return PAGE_ALIGN(sg->offset + sg->length) >> PAGE_SHIFT;
}

bool __sg_page_iter_next(struct sg_page_iter *piter)
{
	if (!piter->__nents || !piter->sg)
		return false;

	piter->sg_pgoffset += piter->__pg_advance;
	piter->__pg_advance = 1;

	while (piter->sg_pgoffset >= sg_page_count(piter->sg)) {
		piter->sg_pgoffset -= sg_page_count(piter->sg);
		piter->sg = sg_next(piter->sg);
		if (!--piter->__nents || !piter->sg)
			return false;
	}
	piter->page = nth_page(sg_page(piter->sg), piter->sg_pgoffset);

	return true;
}
EXPORT_SYMBOL_GPL(__sg_page_iter_next);

void __iomem *devm_ioremap_resource(struct device *dev, struct resource *res)
{
	void __iomem *dest_ptr;

	dest_ptr = devm_ioremap_resource(dev, res);
	if (!dest_ptr)
		return (void __iomem *)ERR_PTR(-ENOMEM);
	return dest_ptr;
}
EXPORT_SYMBOL_GPL(devm_ioremap_resource);

#endif /* __sg_page_iter_next */
