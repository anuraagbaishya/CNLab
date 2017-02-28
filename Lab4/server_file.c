#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<ctype.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAXSIZE 90

main()
{
	int sockfd,newsockfd,retval;
	socklen_t actuallen;
	int recedbytes,sentbytes, ans[MAXSIZE];
	struct sockaddr_in serveraddr,clientaddr;

	char buff[MAXSIZE];
	int a=0;
	FILE *file;

	sockfd=socket(AF_INET,SOCK_STREAM,0);

	if(sockfd==-1)	
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
	
	recedbytes=recv(newsockfd,buff,sizeof(buff),0);

	if(recedbytes==-1)
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
		return EXIT_FAILURE;
	}

	int c;
	int alpha_count = 0, num_count = 0, space_count = 0, other_count = 0;

	printf("\nContents of your file : ");

	while((c=fgetc(file))!=EOF){
		if(isalpha(c))
			alpha_count++;
		else if(isdigit(c))
			num_count++;
		else if(isspace(c))
			space_count++;
		else
			other_count++;
		putchar(c);
	}

	ans[0] = alpha_count;
	ans[1] = num_count;
	ans[2] = space_count;
	ans[3] = other_count;

	fclose(file);

	sentbytes=send(newsockfd,ans,sizeof(ans),0);

	if(sentbytes==-1)
	{
		close(sockfd);
		close(newsockfd);
	}

	close(sockfd);
	close(newsockfd);
}

