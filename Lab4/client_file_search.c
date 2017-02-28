#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAXSIZE 90

main()
{
    int sockfd,retval, count;
    int recdbytes,sentbytes;
    struct sockaddr_in serveraddr;
    char buff[MAXSIZE];
    bool file_op;
    
    //sockfd=socket(AF_INET,SOCK_STREAM,0);
    if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)    
        printf("\nSocket Creation Error");

    printf("Socket ID : %d\n",sockfd);

    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(3388);
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    retval=connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));

    if(retval<0)    
        printf("Connection error\n");
    do{
        printf("Enter file name : " );
        scanf("%s",buff);
        sentbytes=send(sockfd,buff,sizeof(buff),0);

        if(strcmp(buff, "stop") == 0)
            break;

        if(sentbytes==-1)
        {
            printf("!!");
            close(sockfd);
        }

        recdbytes=recv(sockfd,&file_op,sizeof(file_op),0);
        if(!file_op)
        {
            printf("\nFile was not found. Sorry.\n");
            close(sockfd);
            exit(0);
        }

        printf("\nEnter search term : ");
        scanf("%s",buff);
        sentbytes=send(sockfd,buff,sizeof(buff),0);
        if(sentbytes==-1)    
            printf("!!");
        recdbytes = recv(sockfd,&count, sizeof(&count),0);
        printf("Count = %d\n", count);
    }while(strcmp(buff, "stop") != 0);

    close(sockfd);
}
