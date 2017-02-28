#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#define MAXSIZE 50

main()
{
    int sockfd,retval, i;
    int recedbytes,sentbytes;
    struct sockaddr_in serveraddr;
    char buff[MAXSIZE];
    int ans[MAXSIZE];

    sockfd=socket(AF_INET,SOCK_STREAM,0);

    if(sockfd==-1)    
        printf("\nSocket Creation Error");

    printf("Socket ID : %d\n",sockfd);

    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(3388);
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    retval=connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));

    if(retval==-1)    
        printf("Connection error\n");
    
    printf("Enter file name : " );

    scanf("%s",buff);


    sentbytes=send(sockfd,buff,sizeof(buff),0);

    if(sentbytes==-1)
    {
        printf("!!");
        close(sockfd);
    }

    recedbytes=recv(sockfd,ans,sizeof(ans),0);
    printf("\n");
    printf("No of alphabets: %d\n", ans[0]);
    printf("No of digits: %d\n", ans[1]);
    printf("No of special characters: %d\n", ans[2]);
    printf("No of spaces: %d\n", ans[3]);
    printf("\n");
    close(sockfd);
}
