#!/bin/sh

# Connection details
SSH_HOST='robin@192.168.2.70'
INSTALL_DIR='/tmp/robinsdevicedriver'

# Device driver details
module="robinschardevice"
device='robindev'
mode=664
DRIVER_FILES="*.ko *.sh"