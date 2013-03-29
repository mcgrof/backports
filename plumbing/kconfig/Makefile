include versions
export BACKPORTS_VERSION KERNEL_VERSION KERNEL_NAME

menuconfig:
	gcc -Wp,-MD,kconfig/.conf.o.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer   -DCURSES_LOC="<ncurses.h>" -DLOCALE   -c -o kconfig/conf.o kconfig/conf.c
	gcc -Wp,-MD,kconfig/lxdialog/.checklist.o.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer   -DCURSES_LOC="<ncurses.h>" -DLOCALE   -c -o kconfig/lxdialog/checklist.o kconfig/lxdialog/checklist.c
	gcc -Wp,-MD,kconfig/lxdialog/.inputbox.o.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer   -DCURSES_LOC="<ncurses.h>" -DLOCALE   -c -o kconfig/lxdialog/inputbox.o kconfig/lxdialog/inputbox.c
	gcc -Wp,-MD,kconfig/lxdialog/.menubox.o.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer   -DCURSES_LOC="<ncurses.h>" -DLOCALE   -c -o kconfig/lxdialog/menubox.o kconfig/lxdialog/menubox.c
	gcc -Wp,-MD,kconfig/lxdialog/.textbox.o.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer   -DCURSES_LOC="<ncurses.h>" -DLOCALE   -c -o kconfig/lxdialog/textbox.o kconfig/lxdialog/textbox.c
	gcc -Wp,-MD,kconfig/lxdialog/.util.o.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer   -DCURSES_LOC="<ncurses.h>" -DLOCALE   -c -o kconfig/lxdialog/util.o kconfig/lxdialog/util.c
	gcc -Wp,-MD,kconfig/lxdialog/.yesno.o.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer   -DCURSES_LOC="<ncurses.h>" -DLOCALE   -c -o kconfig/lxdialog/yesno.o kconfig/lxdialog/yesno.c
	gcc -Wp,-MD,kconfig/.mconf.o.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer   -DCURSES_LOC="<ncurses.h>" -DLOCALE   -c -o kconfig/mconf.o kconfig/mconf.c
	gcc -Wp,-MD,kconfig/.zconf.tab.o.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer   -DCURSES_LOC="<ncurses.h>" -DLOCALE  -Ikconfig -c -o kconfig/zconf.tab.o kconfig/zconf.tab.c
	gcc  -o kconfig/mconf kconfig/mconf.o kconfig/zconf.tab.o kconfig/lxdialog/checklist.o kconfig/lxdialog/util.o kconfig/lxdialog/inputbox.o kconfig/lxdialog/textbox.o kconfig/lxdialog/yesno.o kconfig/lxdialog/menubox.o  -lncurses
	./kconfig/mconf Kconfig
