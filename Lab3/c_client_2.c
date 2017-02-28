#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#define MAXSIZE 50
#include<time.h>

void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}


main()
{

	pid_t pr_id = fork();
	if(pr_id == 0)
	{
	waitFor(10);
	while(1)
	{
	waitFor(1);
	int sockfd,retval;
	int recedbytes,sentbytes;
	struct sockaddr_in serveraddr;
	char buff[MAXSIZE];
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
	printf("\nSocket Creation Error");
	}
	printf("%i",sockfd);
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3389);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	retval=connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	if(retval==-1)
	{
	printf("Connection error");

	}

	scanf("%s",buff);
	printf("Host B: ");
	sentbytes=send(sockfd,buff,sizeof(buff),0);
	printf("\n");
	if(sentbytes==-1)
	{
		printf("!!");
		close(sockfd);
	}
	close(sockfd);
	}
	}
	else
	{
	while(1)
	{
	int sockfd,newsockfd,retval;
	socklen_t actuallen;
	int recedbytes,sentbytes;
	struct sockaddr_in serveraddr,clientaddr;
	
	char buff[MAXSIZE];
	int a=0;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	
	if(sockfd==-1)
	{
	printf("\nSocket creation error");
	}
	
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3388);
	serveraddr.sin_addr.s_addr=htons(INADDR_ANY);
	retval=bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
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
		printf("Host A : ");
		puts(buff);
		printf("\n");
	
	close(sockfd);
	close(newsockfd);
	}
	}

}		
