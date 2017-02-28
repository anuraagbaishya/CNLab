#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAXSIZE 90

void main()
{
    int sockfd,newsockfd,retval, i, flag = 0;
    socklen_t actuallen;
    int recedbytes,sentbytes, sentans;
    struct sockaddr_in serveraddr,clientaddr;
    int buff[MAXSIZE], s_term, ans[1];
    sockfd=socket(AF_INET,SOCK_STREAM,0);

    if(sockfd==-1)
    {
        printf("\nSocket creation error");
    }

    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(10000);
    serveraddr.sin_addr.s_addr=htons(INADDR_ANY);
    retval=bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    puts("Server Running");
    if(retval==1)
    {
        printf("Binding error");
        close(sockfd);
    }

    retval=listen(sockfd,1);
    if(retval==-1)
    {
        close(sockfd);
    }

    actuallen=sizeof(clientaddr);
    newsockfd=accept(sockfd,(struct sockaddr*)&clientaddr,&actuallen);

    if(newsockfd==-1)
    {
        close(sockfd);
    }
    recedbytes=recv(newsockfd,buff,sizeof(buff),0);
    if(recedbytes==-1)
    {
        close(sockfd);
        close(newsockfd);
    }
    s_term = buff[buff[0]+1];
    for(i = 1; i <= buff[0]; i++)
    {
        if(buff[i] == s_term)
        {
            flag = 1;
            break;
        }
    }
    ans[0] = flag;
    sentbytes = send(newsockfd,ans,sizeof(ans),0);
    close(sockfd);
    close(newsockfd);
    
}

