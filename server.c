#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define MAX 80
#define PORT 36744
#define SA struct sockaddr

void func(int sockfd)
{char buff[MAX];
int n;
for(;;)
{
bzero(buff,MAX);
read(sockfd,buff,sizeof(buff));
printf("From client: %s\t To client : ",buff);
bzero(buff,MAX);
n=0;
while((buff[n++]=getchar())!='\n');
write(sockfd,buff,sizeof(buff));

if(strncmp("assalamualaikum",buff,15)==0)
{
printf("From client: waalaikumussalam\n");
printf("\tTo client : ");
bzero(buff,MAX);
n=0;
while((buff[n++]=getchar())!='\n');
write(sockfd,buff,sizeof(buff));
}

if(strncmp("assalamualaikum",buff,15)!=0)
{
printf("From client: are u a muslim?\n");
printf("\tTo client : ");
bzero(buff,MAX);
n=0;
while((buff[n++]=getchar())!='\n');
write(sockfd,buff,sizeof(buff));}

if(strncmp("exit",buff,4)==0)
{
printf("Server Exit..\n");
break;
}
}
}
int main()
{
int sockfd,connfd,len;
struct sockaddr_in servaddr,cli;
sockfd=socket(AF_INET,SOCK_STREAM,0);
if (sockfd==-1)
{
printf("socket creation failed...\n");
exit(0);
}else
printf("Socket succesfully created...\n");
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
printf("socket successfully binded\n");

if((listen(sockfd,5))!=0)
{
printf("Listen failed\n");
exit(0);
}
else
printf("server listening\n");
len=sizeof(cli);
connfd=accept(sockfd,(SA*)&cli,&len);

if(connfd<0)
{
printf("server accept failed\n");
exit(0);
}else
printf("server accept the client\n");
func(connfd);
close(sockfd);
}


# assignment1
