#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>

#include<assert.h>
#include<string.h>
#include<stdio.h>

#include"unp.h"

void dg_echo(FILE *fp,int fd,struct sockaddr_in* pservaddr,socklen_t len)
{
  char send_buf[1024] = {0};
  char servaddr_buf[50] = {0};
  inet_ntop(AF_INET,&(pservaddr->sin_addr.s_addr),servaddr_buf,sizeof(servaddr_buf));

  printf("cli sendto %s ,port:%d\n",servaddr_buf,pservaddr->sin_port);
  for(;;){
    fgets(send_buf,sizeof(send_buf),fp);
    printf("sendbuf:%s\n",send_buf);
    sendto(fd,send_buf,sizeof(send_buf),0,(struct sockaddr *)pservaddr,len);
  }

}

int main(int argc,const char*argv[])
{
  int fd;
  struct sockaddr_in serv_addr,cliaddr;
  fd = socket(AF_INET,SOCK_DGRAM,0);
  assert(fd);

 /****dont need client addr 
  bzero(&cliaddr,sizeof(cliaddr));
  cliaddr.sin_famaily = AF_INET;
  cliaddr.sin_addr.saddr = htonl(ADDR_ANY);
  cliaddr.sin_addr.port = htons();
*****/
  bzero(&serv_addr,sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  //serv_addr.sin_addr.s_addr = htonl(ADDR_ANY);
  inet_pton(AF_INET,argv[1],&(serv_addr.sin_addr.s_addr));
  serv_addr.sin_port = htons(SERV_PORT);

  dg_echo(stdin,fd,&serv_addr,sizeof(serv_addr));
}
