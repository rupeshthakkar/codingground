#!/bin/bash
#
# myservice_ctl This script starts and stops the mysql-proxy daemon
#
# chkconfig: 3 78 30
# processname: myservice_ctl
# description: myservice_ctl is a proxy daemon for myservice

path="myservice"
case "$1" in
  start)
        echo -n "Starting myservice"
        echo -n ""
        PID=`pidof -s myservice`
        #To run it as root:
        if [ "$PID" != "" ]; then
          echo -n "Process already running"
        else
         `$path > /dev/null 2>&1`&
        fi
        ;;
  stop)
        echo -n "Stopping myservice"
        echo -n ""
        PID=`pidof -s myservice`
        if [ $? -eq 0 ]; then
          kill $PID > /dev/null 2>&1
          sleep 5;
        else
         echo -n "Process not running"
        fi
        ;;
  *)
        echo -n "Usage: /sbin/service myservice {start|stop}"
        exit 1
esac
exit 0
