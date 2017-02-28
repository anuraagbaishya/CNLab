#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAXSIZE 150

int flag = 0;

char* encrypt(char* str){
    int i;
    for(i=0; str[i] != '\0'; i++)
        str[i] = str[i] - 15;
    return str;
}

void main()
{
    int sockfd,newsockfd,retval;
    socklen_t actuallen;
    int recedbytes,sentbytes, sentans;
    struct sockaddr_in serveraddr,clientaddr;

    char buff[MAXSIZE], ans[MAXSIZE];
    char* temp_buf;
    int a=0;
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
        //close(sockfd);
    }

    retval=listen(sockfd,1);
    if(retval==-1)
    {
        //close(sockfd);
    }

    actuallen=sizeof(clientaddr);
    newsockfd=accept(sockfd,(struct sockaddr*)&clientaddr,&actuallen);


    if(newsockfd==-1)
    {
        //close(sockfd);
    }

    //puts(buff);
    do{
        recedbytes=recv(newsockfd,buff,sizeof(buff),0);
        if(strcmp(buff, "stop") == 0)
        {
            puts("Stopping");
            close(sockfd);
            close(newsockfd);    
        }
        else
        {
            temp_buf = encrypt(buff);
            puts(temp_buf);
            sentbytes = send(newsockfd,temp_buf,sizeof(temp_buf),0);
       }
   }while(strcmp(buff, "stop") != 0);
    
}

