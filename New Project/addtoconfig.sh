#!/usr/bin/bash

cp ./myservice_ctl.sh /etc/init.d/myservice_ctl
chkconfig myservice_ctl --add
chkconfig myservice_ctl --list
