#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#include<assert.h>
#include<string.h>

#include "unp.h"
int dg_echo(int fd,struct sockaddr *pcliaddr,socklen_t clilen)
{
   int n;
   char buf[1024] = {0};
   socklen_t len;
   for( ; ;)
   {
     //len
     n = recvfrom(fd,buf,sizeof(buf),0,pcliaddr,&len);
     printf("recvform ip:%s context:%s\n",inet_ntoa(((struct sockaddr_in *)pcliaddr)->sin_addr),buf);

   }
}
int main()
{
  int fd;
  struct sockaddr_in serv_addr,cliaddr;

  fd = socket(AF_INET,SOCK_DGRAM,0);
  assert(fd);

  bzero(&serv_addr,sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(SERV_PORT);
  printf("SERV_PORT:%d ,serv_addr.sin_port:%d\n",SERV_PORT,serv_addr.sin_port);
  
  bind(fd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));

  dg_echo(fd,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
}
