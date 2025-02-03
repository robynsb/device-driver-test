#!/usr/bin/env bash

. ./driver-config.sh

if [[ -n  "$(lsmod | grep $module)" ]]; then
    rmmod $module.ko
    rm -f /dev/${device}[0-3]
fi