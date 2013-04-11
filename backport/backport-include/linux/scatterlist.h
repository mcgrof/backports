#ifndef __BACKPORT_SCATTERLIST_H
#define __BACKPORT_SCATTERLIST_H
#include_next <linux/scatterlist.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,9,0)

/* Lets expect distributions might backport this */
#ifndef for_each_sg_page
/*
 * sg page iterator
 *
 * Iterates over sg entries page-by-page.  On each successful iteration,
 * @piter->page points to the current page, @piter->sg to the sg holding this
 * page and @piter->sg_pgoffset to the page's page offset within the sg. The
 * iteration will stop either when a maximum number of sg entries was reached
 * or a terminating sg (sg_last(sg) == true) was reached.
 */
struct sg_page_iter {
	struct page		*page;		/* current page */
	struct scatterlist	*sg;		/* sg holding the page */
	unsigned int		sg_pgoffset;	/* page offset within the sg */

	/* these are internal states, keep away */
	unsigned int		__nents;	/* remaining sg entries */
	int			__pg_advance;	/* nr pages to advance at the
						 * next step */
};

#define __sg_page_iter_next LINUX_BACKPORT(__sg_page_iter_next)
bool __sg_page_iter_next(struct sg_page_iter *piter);
#define __sg_page_iter_start LINUX_BACKPORT(__sg_page_iter_start)
void __sg_page_iter_start(struct sg_page_iter *piter,
			  struct scatterlist *sglist, unsigned int nents,
			  unsigned long pgoffset);

/**
 * for_each_sg_page - iterate over the pages of the given sg list
 * @sglist:	sglist to iterate over
 * @piter:	page iterator to hold current page, sg, sg_pgoffset
 * @nents:	maximum number of sg entries to iterate over
 * @pgoffset:	starting page offset
 */
#define for_each_sg_page(sglist, piter, nents, pgoffset)		   \
	for (__sg_page_iter_start((piter), (sglist), (nents), (pgoffset)); \
	     __sg_page_iter_next(piter);)

#endif /* for_each_sg_page assumption */
#endif /* version < 3.9 */

#endif /* __BACKPORT_SCATTERLIST_H */
