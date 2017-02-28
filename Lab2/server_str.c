#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAXSIZE 90

char *strlwr(char *str)
{
  unsigned char *p = (unsigned char *)str;

  while (*p) {
     *p = tolower(*p);
      p++;
  }

  return str;
}

void main()
{
    int sockfd,newsockfd, i, retval, n = 0;
    socklen_t actuallen;
    int recedbytes,sentbytes, ans[2];
    struct sockaddr_in serveraddr,clientaddr;
    char buff[MAXSIZE]; char* buf;
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
    do{
        recedbytes=recv(newsockfd,buff,sizeof(buff),0);
        if(recedbytes==-1)
        {
            //close(sockfd);
            //close(newsockfd);
        }
        if(strcmp(buff, "stop") == 0)
        {
            puts("Stopping");
            close(sockfd);
            close(newsockfd);    
        }
        else
        {
            n = 0;
            ans[0] = strlen(buff);
            strlwr(buff);
            puts(buff);
            for(i = 0; buff[i]!='\0'; i++)
                if(buff[i] == 'a' || buff[i] == 'e' || buff[i] == 'i' || buff[i] == 'o' || buff[i] == 'u')
                    n++;    
            ans[1] = n;
            sentbytes = send(newsockfd,ans,sizeof(ans),0);
        }
    }while(strcmp(buff, "stop") != 0);
}

