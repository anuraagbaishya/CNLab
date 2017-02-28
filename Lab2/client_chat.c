#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#define MAXSIZE 150

void main()
{
    int sockfd,retval;
    int recedbytes,sentbytes, recans;
    struct sockaddr_in serveraddr;
    char buff[MAXSIZE], ans[MAXSIZE], test[MAXSIZE];
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1)
    {
        printf("\nSocket Creation Error");

    }
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(10000);
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    retval=connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if(retval==-1)
    {
        printf("Connection error");
    }
    do{
        scanf("%s",buff);
        if(strcmp(buff, "Bye") == 0)
        {
            puts("Exiting");
            sentbytes=send(sockfd,buff,sizeof(buff),0);
            close(sockfd);
            break;
        }
        sentbytes=send(sockfd,buff,sizeof(buff),0);
        recedbytes=recv(sockfd,ans,sizeof(ans),0);
        puts(ans);
        
    }while(strcmp(buff, "Bye") != 0);
}
