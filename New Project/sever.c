
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <pthread.h>
//follwing needed in some env
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/wait.h>


int keeprunning=1;
pthread_mutex_t mutex;
void get_random(char outstring[],int count);
void error(const char *msg);
void demonize();
void* handle_request (void *ptr);
static void handle_sigterm (int sig);

int main()
{

  int sockfd, newsockfd, portno,ret;
  socklen_t clilen;
  struct sockaddr_in serv_addr, cli_addr;
  struct sigaction sigact,act;
 
  //demonize();
  memset (&sigact, '\0', sizeof(sigact));
  sigact.sa_handler = &handle_sigterm;
  if (sigaction(SIGTERM, &sigact, NULL) < 0) 
  {
    perror ("sigaction");
	return 1;
  }
  
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd > 0)
  {
     memset((char *) &serv_addr,'\0', sizeof(serv_addr));
     portno = 8787;
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");
     printf("Server listening \n");
     listen(sockfd,100);
     clilen = sizeof(cli_addr);
     pthread_t tid[100];
     int client_fds[100];
     int *ptr = NULL,cnt=-1;
     pthread_mutex_init(&mutex, NULL);
    
    
     while(keeprunning && ++cnt <100)
     {
       client_fds[cnt] = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
       if (client_fds[cnt] < 0)
            error("ERROR on accept");
       ret = pthread_create(&tid[cnt], NULL, &handle_request, (void*) &(client_fds[cnt]));
       
       if(ret)
       {
         fprintf(stderr,"Error - pthread_create() return code: %d\n",ret);
         exit(EXIT_FAILURE);
       }

       ret = pthread_detach(tid[cnt]);
       if(ret)
       {
         fprintf(stderr,"Error - pthread_deatch() return code: %d\n",ret);
         exit(EXIT_FAILURE);
       }
      

     }
    
     close(sockfd);
     pthread_mutex_destroy(&mutex);
     return 0;

  }
  pthread_exit(0);
  return 0;
}


void* handle_request (void *ptr)
{
    char buffer[256];
    char message[50];
    int client_fd,n=0;
    pthread_mutex_lock(&mutex);
    client_fd = *((int *)ptr);
    pthread_mutex_unlock(&mutex);
 
    memset((char *) &buffer,'\0', sizeof(buffer));
    
    while(strcmp(buffer,"BYE")!=0)
    {
       memset((char *) &buffer,'\0', sizeof(buffer));
       memset((char *) &message,'\0', sizeof(message));
       n = read(client_fd,buffer,10);
       if (n < 0) error("ERROR reading from socket");
       printf("Here is client message: %s\n",buffer);  
     
       if(strcmp(buffer,"GETMESSAGE")!=0)
         strcpy(message,"Bad Request");
       else
         get_random(message,50);
       n = write(client_fd,message,strlen(message));
       if (n < 0) error("ERROR in writing socket");
    }
    
    close(client_fd);
    return ptr;
}
void get_random(char outstring[],int count)
{
    int i=0,base=126-32;
    //get printable ascii character between 32-126
    for(i=0;i<count-1;i++)
      outstring[i]=toascii((rand()%base)+32);
    outstring[i]='\0';

}
void error(const char *msg)
{
    perror(msg);
    exit(1);
}
static void handle_sigterm (int sig)
{

    printf("SIGTERM CALLED\n");
	keeprunning=0;
}

void demonize()
{
  pid_t sid,pid;
      
  return; //since need to tune this for defunc process      
  
  pid = fork();
  if (pid < 0) {
    //exit(EXIT_FAILURE);
  }
  if(pid > 0) {
    //exit(EXIT_SUCCESS);
  }
  
  /* Change the file mode mask */
  umask(0);
  sid = setsid();
  if(sid < 0) {
      exit(EXIT_FAILURE);
  }
  if(chdir("/") < 0){
      exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  
}
