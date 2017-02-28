#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<ctype.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdbool.h>
#define MAXSIZE 90

int word_frequency(FILE* f, char search[])
{
	int count=0;
	char temp[1024];
	while(fscanf(f, "%s", temp) == 1)
	{
		if(strcmp(temp,search) == 0)
			count++;
	}

	return count;
}

main()
{
	int sockfd,newsockfd,retval, i;
	socklen_t actuallen;
	int recdbytes,sentbytes, ans;
	struct sockaddr_in serveraddr,clientaddr;
	char buff[MAXSIZE];
	bool file_found=false;
	int count=0;
	FILE *file;

	//sockfd=socket(AF_INET,SOCK_STREAM,0);

	if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)	
		printf("\nSocket creation error");	

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
		close(sockfd);
	
	actuallen=sizeof(clientaddr);
	newsockfd=accept(sockfd,(struct sockaddr*)&clientaddr,&actuallen);


	if(newsockfd==-1)
		close(sockfd);	
	
	do{
		recdbytes=recv(newsockfd,buff,sizeof(buff),0);
		if(strcmp(buff, "stop") == 0)
			break;

		if(recdbytes==-1)
		{
			close(sockfd);
			close(newsockfd);
		}

		printf("The name of your file is : ");
		puts(buff);
		printf("\n");
		
		file = fopen(buff, "r");
		if(!file){
			perror("Error opening file.");
			strcpy(buff, "File not found.");
			puts(buff);
			return EXIT_FAILURE;
		}

		file_found=true;
		sentbytes=send(newsockfd,&file_found,sizeof(file_found),0);

		if(sentbytes==-1)
		{
			close(sockfd);
			close(newsockfd);
		}

		recdbytes = recv(newsockfd,buff,sizeof(buff),0);
		count = word_frequency(file,buff);
		for(i = 0; i < 10000; i++);

			sentbytes=send(newsockfd,&count,sizeof(count),0);
	}while(strcmp(buff, "stop") != 0);

	close(sockfd);
	close(newsockfd);
}

