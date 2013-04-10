#!/bin/bash

set -e

function mod_filename()
{
	which modinfo > /dev/null 2>&1
	if [[ $? -eq 0 ]]; then
		MOD_QUERY="modinfo -F filename"
	else
		MOD_QUERY="modprobe -l"
	fi
	mod_path="$($MOD_QUERY $1 | tail -1)"
	echo $(basename "$mod_path")
}

test "$(mod_filename mac80211)" = "mac80211.ko.gz" &&
	for driver in $(find "$1" -type f -name *.ko); do
		gzip -9 $driver
	done
