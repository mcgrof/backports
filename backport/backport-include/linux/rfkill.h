#ifndef __COMPAT_RFKILL_H
#define __COMPAT_RFKILL_H
#include <linux/version.h>

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,33))
#include_next <linux/rfkill.h>
#else
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,31)
#define rfkill_get_led_trigger_name LINUX_BACKPORT(rfkill_get_led_trigger_name)
#define rfkill_set_led_trigger_name LINUX_BACKPORT(rfkill_set_led_trigger_name)
#define rfkill_set_hw_state LINUX_BACKPORT(rfkill_set_hw_state)
#define rfkill_set_sw_state LINUX_BACKPORT(rfkill_set_sw_state)
#define rfkill_init_sw_state LINUX_BACKPORT(rfkill_init_sw_state)
#define rfkill_set_states LINUX_BACKPORT(rfkill_set_states)
#define rfkill_pause_polling LINUX_BACKPORT(rfkill_pause_polling)
#define rfkill_resume_polling LINUX_BACKPORT(rfkill_resume_polling)
#define rfkill_blocked LINUX_BACKPORT(rfkill_blocked)
#define rfkill_alloc LINUX_BACKPORT(rfkill_alloc)
#define rfkill_register LINUX_BACKPORT(rfkill_register)
#define rfkill_unregister LINUX_BACKPORT(rfkill_unregister)
#define rfkill_destroy LINUX_BACKPORT(rfkill_destroy)
#endif
#include <linux/rfkill_backport.h>
#endif

#endif
