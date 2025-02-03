#!/bin/sh

. ./driver-config.sh

scp $DRIVER_FILES $SSH_HOST:$INSTALL_DIR
ssh $SSH_HOST "cd $INSTALL_DIR && sudo ./remove-driver.sh && sudo ./install-driver.sh"