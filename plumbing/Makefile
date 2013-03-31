#
# Makefile for the output source package
#

ifeq ($(KERNELRELEASE),)

MAKEFLAGS += --no-print-directory
SHELL = /bin/bash
BACKPORT_PWD := $(shell pwd)

KLIB_BUILD ?= /lib/modules/$(shell uname -r)/build/
KERNEL_CONFIG := $(KLIB_BUILD)/.config
CONFIG_MD5 := $(shell md5sum $(KERNEL_CONFIG) | sed 's/\s.*//')

export KLIB_BUILD BACKPORT_PWD

# disable built-in rules for this file
.SUFFIXES:

.PHONY: default
default:
	@$(MAKE) modules

.DEFAULT:
	@set -e ; if [ "$$(cat .kernel_config_md5 2>/dev/null)" != "$(CONFIG_MD5)" ]	;\
	then 										\
		echo -n "Generating local configuration database from kernel ..."	;\
		grep -v -f .local-symbols $(KERNEL_CONFIG) | grep = | (			\
			while read l ; do						\
				if [ "$${l:0:7}" != "CONFIG_" ] ; then			\
					continue					;\
				fi							;\
				l=$${l:7}						;\
				n=$${l%%=*}						;\
				v=$${l#*=}						;\
				if [ "$$v" = "m" ] ; then				\
					echo config $$n					;\
					echo '    tristate' 				;\
				elif [ "$$v" = "y" ] ; then				\
					echo config $$n					;\
					echo '    bool'					;\
				else							\
					continue					;\
				fi							;\
				echo "    default $$v"					;\
				echo ""							;\
			done								\
		) > Kconfig.kernel							;\
		kver=$$($(MAKE) --no-print-directory -C $(KLIB_BUILD) kernelversion |	\
			sed 's/^\(\(3\|2\.6\)\.[0-9]\+\).*/\1/;t;d')			;\
		test "$$kver" != "" || echo "Kernel version parse failed!"		;\
		test "$$kver" != ""							;\
		kvers="$$(seq 14 39 | sed 's/^/2.6./')"					;\
		kvers="$$kvers $$(seq 0 99 | sed 's/^/3./')"				;\
		print=0									;\
		for v in $$kvers ; do							\
			if [ "$$print" = "1" ] ; then					\
				echo config BACKPORT_KERNEL_$$(echo $$v | tr . _)	;\
				echo "    def_bool y"					;\
			fi								;\
			if [ "$$v" = "$$kver" ] ; then print=1 ; fi			;\
		done > Kconfig.versions							;\
		echo " done."								;\
	fi										;\
	echo "$(CONFIG_MD5)" > .kernel_config_md5
	@#test -f .config && $(MAKE) -f Makefile.real oldconfig || true
	@$(MAKE) -f Makefile.real "$@"

else
include $(BACKPORT_PWD)/Makefile.kernel
endif
