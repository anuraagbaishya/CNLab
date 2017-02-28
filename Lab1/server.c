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
    int sockfd,newsockfd,retval, i, j, n, swap;
    socklen_t actuallen;
    int recedbytes,sentbytes, sentans;
    struct sockaddr_in serveraddr,clientaddr;
    int buff[MAXSIZE], s_term;
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
    n = buff[0];
    for (i = 1 ; i <= n ; i++)
    {
        for (j = 1 ; j <= n - i; j++)
        {
            if (buff[j] > buff[j+1]) /* For decreasing order use < */
            {
                swap       = buff[j];
                buff[j]   = buff[j+1];
                buff[j+1] = swap;
            }
        }
    } 
    for(i = 1; i <= n; i++)
        printf("%d\n", buff[i]);   
    sentbytes = send(newsockfd,buff,sizeof(buff),0);
}

