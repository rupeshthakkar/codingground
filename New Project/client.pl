#!/usr/bin/perl -w                                                                                                                                                                 
# Filename : client.pl                                                                                                                                                             
use strict;                                                                                                                                                                        
use Socket;                                                                                                                                                                        
use IO::Socket::INET;  
if ( @ARGV > 0 )                                                                                                                                                                   
{                                                                                                                                                                                  
   #print "Number of arguments: " . scalar @ARGV . "\n";                                                                                                                            
}                                                                                                                                                                                  
else                                                                                                                                                                               
{                                                                                                                                                                                  
   print "Insufficient number of argument required\n";                                                                                                                               
   print "Usage $0 tcp_server server_port_no number_of_clients\n";
   exit(0);                                                                                                                                                                        
}                                                                                                                                                                                  
# initialize host and port_no                                                                                                                                                      
my $server = shift || 'localhost';                                                                                                                                                   
my $port_no = shift || 8787;                                                                                                                                                       
my $num_clients = shift || 1;  
my $data ="";

#my $server = "localhost";  # Host IP running the server                                                                                                                            
for(my $i=0; $i < $num_clients ; $i++)                                                                                                                                             
{                                                                                                                                                                                  
  if(my $pid=fork)                                                                                                                                                                 
  {                                                                                                                                                                                
    #print "I M parent $$ got child's PID as $pid\n";                                                                                                                               
    #exit(0);                                       
  }                                                                                                                                                                                
  else                                                                                                                                                                             
  {                                                                                                                                                                                
    my $remote = IO::Socket::INET->new( Proto     => "tcp",
                                         PeerAddr  => $server,
                                         PeerPort  => $port_no,
                  )     || die "cannot connect to $server";
    $remote->autoflush(1);
    #print $remote "GETMESSAGE";
    $remote->send("GETMESSAGE");
    #while ( <$remote> ) { print }
    $remote->autoflush(1);
    $remote->recv($data,1024);
    print "\nC: server Message";
    print $data;
    $remote->send("BYE");
    $remote->close();
    #close $remote;                                                                                                                                           
    exit(0);                                                                                                                                                                       
  }                                                                                                                                                                                
}                                                                                                                                                                                  
                                                                                                                                                                                   
                                                                                                                                                                                   
while (wait() != -1)                                                                                                                                                               
{                                                                                                                                                                                  
  #print "Client waiting\n";                                                                                                                                                          
}                                                                                                          

print "Client Finished\n";                                                                                                                                                         
                                                                                                                                                                                   
exit(0);
