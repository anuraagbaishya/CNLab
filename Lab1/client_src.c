#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#define MAXSIZE 50

void main()
{
    int sockfd,retval;
    int recedbytes,sentbytes, recans;
    struct sockaddr_in serveraddr;
    int buff[MAXSIZE], ans[1], n, i;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1)
    {
        printf("\nSocket Creation Error");

    }
    printf("\nSocket ID : %d\n",sockfd);
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(10000);
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    retval=connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if(retval==-1)
    {
        printf("Connection error");
    }
    printf("Enter no. of terms: ");
    scanf("%d", &n);
    buff[0] = n;
    printf("Enter terms: ");
    for(i = 1; i <= n; i++)
        scanf("%d", &buff[i]);
    printf("Enter term to search: ");
        scanf("%d", &buff[i]);
    sentbytes = send(sockfd,buff,sizeof(buff),0);
    recedbytes=recv(sockfd,ans,sizeof(ans),0);
    if(ans[0] == 1)
        printf("%s", "Element Found\n");
    else
        printf("%s", "Element Not Found\n");
    close(sockfd);
}
