#ifndef __BACKPORT_INPUT_H
#define __BACKPORT_INPUT_H
#include_next <linux/input.h>

#ifndef KEY_WIMAX
#define KEY_WIMAX		246
#endif

#endif /* __BACKPORT_INPUT_H */
