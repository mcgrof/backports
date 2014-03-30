#ifndef _BACKPORTS_LINUX_STATIC_KEY_H
#define _BACKPORTS_LINUX_STATIC_KEY_H 1

#include <linux/version.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,3,0) /* kernels >= 3.3 */
/*
 * XXX: NOTE!
 *
 * Some 3.3 kernels carry <linux/static.h> but some don't even though its
 * its including <linux/jump_label.h>. What makes it more confusing is that
 * later all this got shuffled. The safe thing to do then is to just assume
 * kernels 3.3..3.4 don't have it and include <linux/jump_label.h> instead,
 * and for newer kernels include <linux/static_key.h>.
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,5,0)
#include_next <linux/static_key.h>
#else
#include <linux/jump_label.h>
#endif

#else /* kernels < 3.3 */
/*
 * in between 2.6.37 - 3.5 there's a slew of changes that make
 * it hard to backport this properly. If you are interested in
 * trying you can use this as reference:
 *
 * http://drvbp1.linux-foundation.org/~mcgrof/examples/2014/04/01/backport-static-keys.patch
 *
 * And these notes:
 *
 *           < v2.6.37 - No tracing support
 * bf5438fc  - v2.6.37 - Jump label support added primarily for tracing but
 *                       tracing was broken, later kernels started sporting
 *                       functional tracing.
 * d430d3d7e - v3.0    - Static branch optimizations for jump labels
 * c5905afb  - v3.3    - Static keys split out, note on the below issue
 * c5905afb  - v3.5    - git describe --contains c5905afb claims but not true!
 * c4b2c0c5f - v3.13   - Adds static_key_initialized(), STATIC_KEY_CHECK_USE()
 *
 * Because all of this we skip 2.6.37 - 3.3 but and adding support for older
 * can be done by of carrying over the non-architecture optimized code.
 * Carrying new changes into this file is a burden though so if we really
 * find use for this we could just split the non optimized versions upstream
 * and copy that through an automatic process.
 */

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,37)
/*
 * For kernels older than 2.6.37 we just take on the
 * implementation in the kernel that assumes you have
 * either no toolchain or architecture kernel support
 * for the jump labels. Daring folks who wish to embark
 * on a nutty journey may wish to see if they can backport
 * architectural specific changes here.
 *
 * Jump label support was added via commit
 * bf5438fca2950b03c21ad868090cc1a8fcd49536 through kernel
 * v2.6.37-rc1~214^2~33^2~8
 */

/*
 * Jump label support
 *
 * Copyright (C) 2009-2012 Jason Baron <jbaron@redhat.com>
 * Copyright (C) 2011-2012 Peter Zijlstra <pzijlstr@redhat.com>
 *
 * Jump labels provide an interface to generate dynamic branches using
 * self-modifying code. Assuming toolchain and architecture support the result
 * of a "if (static_key_false(&key))" statement is a unconditional branch (which
 * defaults to false - and the true block is placed out of line).
 *
 * However at runtime we can change the branch target using
 * static_key_slow_{inc,dec}(). These function as a 'reference' count on the key
 * object and for as long as there are references all branches referring to
 * that particular key will point to the (out of line) true block.
 *
 * Since this relies on modifying code the static_key_slow_{inc,dec}() functions
 * must be considered absolute slow paths (machine wide synchronization etc.).
 * OTOH, since the affected branches are unconditional their runtime overhead
 * will be absolutely minimal, esp. in the default (off) case where the total
 * effect is a single NOP of appropriate size. The on case will patch in a jump
 * to the out-of-line block.
 *
 * When the control is directly exposed to userspace it is prudent to delay the
 * decrement to avoid high frequency code modifications which can (and do)
 * cause significant performance degradation. Struct static_key_deferred and
 * static_key_slow_dec_deferred() provide for this.
 *
 * Lacking toolchain and or architecture support, it falls back to a simple
 * conditional branch.
 *
 * struct static_key my_key = STATIC_KEY_INIT_TRUE;
 *
 *   if (static_key_true(&my_key)) {
 *   }
 *
 * will result in the true case being in-line and starts the key with a single
 * reference. Mixing static_key_true() and static_key_false() on the same key is not
 * allowed.
 *
 * Not initializing the key (static data is initialized to 0s anyway) is the
 * same as using STATIC_KEY_INIT_FALSE.
 *
*/

#include <linux/types.h>
#include <linux/compiler.h>
#include <linux/bug.h>

/*
 * For the backport we leave out static_key_initialized as
 * no architecture code is provided to support jump labels, so
 * we treat jump labels as simply atomic values which drive
 * branches. Since we don't backport static_key_initialized
 * we leave out all STATIC_KEY_CHECK_USE() uses.
 */

enum jump_label_type {
	JUMP_LABEL_DISABLE = 0,
	JUMP_LABEL_ENABLE,
};

struct module;

#include <linux/atomic.h>

struct static_key {
	atomic_t enabled;
};

static __always_inline bool static_key_false(struct static_key *key)
{
	if (unlikely(atomic_read(&key->enabled) > 0))
		return true;
	return false;
}

static __always_inline bool static_key_true(struct static_key *key)
{
	if (likely(atomic_read(&key->enabled) > 0))
		return true;
	return false;
}

static inline void static_key_slow_inc(struct static_key *key)
{
	atomic_inc(&key->enabled);
}

static inline void static_key_slow_dec(struct static_key *key)
{
	atomic_dec(&key->enabled);
}

static inline int jump_label_text_reserved(void *start, void *end)
{
	return 0;
}

static inline void jump_label_lock(void) {}
static inline void jump_label_unlock(void) {}

static inline int jump_label_apply_nops(struct module *mod)
{
	return 0;
}

#define STATIC_KEY_INIT_TRUE ((struct static_key) \
		{ .enabled = ATOMIC_INIT(1) })
#define STATIC_KEY_INIT_FALSE ((struct static_key) \
		{ .enabled = ATOMIC_INIT(0) })


#define STATIC_KEY_INIT STATIC_KEY_INIT_FALSE
#define jump_label_enabled static_key_enabled

static inline bool static_key_enabled(struct static_key *key)
{
	return (atomic_read(&key->enabled) > 0);
}

#endif /* kernels older than 2.6.37  */
#endif /* kernels < 3.3 */

#endif /* _BACKPORTS_LINUX_STATIC_KEY_H */
