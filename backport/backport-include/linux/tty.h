#ifndef __BACKPORT_LINUX_TTY_H
#define __BACKPORT_LINUX_TTY_H
#include_next <linux/tty.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39) && \
    LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,27)
#define tty_set_termios LINUX_BACKPORT(tty_set_termios)
extern int tty_set_termios(struct tty_struct *tty, struct ktermios *kt);
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,7,0)
/* Backports tty_lock: Localise the lock */
#define tty_lock(__tty) tty_lock()
#define tty_unlock(__tty) tty_unlock()

#define tty_port_register_device(port, driver, index, device) \
	tty_register_device(driver, index, device)
#endif

#endif /* __BACKPORT_LINUX_TTY_H */
