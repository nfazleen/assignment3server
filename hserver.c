#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define MAX 80
#define PORT 36744
#define SA struct sockaddr

void checkHostName(int hostname)
{
if(hostname==-1)
{
perror("gethostname");
exit(1);
}
}

void func(int sockfd)
{
char buff[MAX];
int n;
char hostbuffer[256];
int hostname;
for(;;)
{
bzero(buff,MAX);
read(sockfd,buff,sizeof(buff));
printf("From client:%s\t To client: ",buff);
bzero(buff,MAX);
n=0;
while((buff[n++]=getchar())!='\n');
write(sockfd,buff,sizeof(buff));

if(strncmp(buff,"a",1)==0)
{
hostname=gethostname(hostbuffer,sizeof(hostbuffer));
checkHostName(hostname);
printf("Hostname: %s\n",hostbuffer);
write(sockfd,buff,sizeof(buff));
printf("From client:%s",buff);
}

if(strncmp("exit",buff,4)==0)
{
printf("Server Exit\n");
break;
}
}
}

int main()
{
int sockfd,connfd,len;
struct sockaddr_in servaddr,cli;
sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd==-1)
{
printf("Socket fail to create\n");
exit(0);
}
else
printf("Socket created\n");
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
servaddr.sin_port=htons(PORT);

if((bind(sockfd,(SA*)&servaddr,sizeof(servaddr)))!=0)
{
printf("socket bin failed\n");
exit(0);
}
else
printf("Socket successfully binded\n");

if((listen(sockfd,5))!=0)
{
printf("Listen failed\n");
exit(0);
}
else
printf("Server listening\n");
len=sizeof(cli);
connfd=accept(sockfd,(SA*)&cli, &len);

if(connfd<0)
{
printf("Server accept failed\n");
exit(0);
}
else
printf("Server accept the Client\n");
func(connfd);
close(sockfd);
}
