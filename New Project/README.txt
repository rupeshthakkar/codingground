1)Server excecution
a)myservice
The server excutable provided myservice should work RHEL6 64 bit(I have compiled it under Fedora release 21).
b)If excutable do not work, can be compliled with following step
  gcc -o myservice -lpthread server.c 
c)Start the server as as below, it will listen on port 8787 on both ip
sh-4.3# myservice &
d)server is multi threaded for 100 connection, threads are created as connections requests comes insteas threadpool

2)Client 
Client is perl script requires 3 inputs 1) serverip 2) port 3) numberclient connections user want to run
for example
sh-4.3# ./client.pl 172.17.90.220 8787 10
sh-4.3# ./client.pl localhost 8787 20

3)Startup scripts
a)copy both addconfig.sh and myservice_ctl.sh to same linux directory
b)execute ./addconfig.sh as root
c)service can be start and stop as below
service myservice_ctl start (OR /etc/init.d/myservice_ctl start)
service myservice_ctl stop (OR /etc/init.d/myservice_ctl stop)


4)README.txt
The README.txt(this file) contains information how to execute server and client


Note : The currenlty server runs only at port 8787.
       Demonizing part of server still needs some changes