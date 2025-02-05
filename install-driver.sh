#!/usr/bin/env bash

. ./driver-config.sh

insmod $module.ko

major=$(awk -v device="$device" '$2 == device { print $1 }' /proc/devices)

mknod /dev/${device}0 c $major 0
mknod /dev/${device}1 c $major 1
mknod /dev/${device}2 c $major 2
mknod /dev/${device}3 c $major 3

if grep -q '^staff:' /etc/group; then
    group="staff"
else
    group="wheel"
fi
chgrp $group /dev/${device}[0-3] 
chmod $mode  /dev/${device}[0-3]
