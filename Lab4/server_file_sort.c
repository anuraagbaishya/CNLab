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

int store_strings(FILE* file, char arr[MAXSIZE])
{
	int n=0, c;
   	while ((c = fgetc(file)) != EOF)
    {
        arr[n++] = (char) c;
    }
    arr[n] = '\0';
    return n;
}

void sort(char array[MAXSIZE], int n)
{
	int i, j;
	char swap;
	for (i = 0 ; i < (n - 1); i++)
  	{
    	for (j = 0 ; j<n - i - 1; j++)
    	{
      		if (array[j] > array[j+1]) /* For decreasing order use < */
      		{
        		swap       = array[j];
        		array[j]   = array[j+1];
        		array[j+1] = swap;
      		}
    	}
    }	
}
main()
{
	int sockfd,newsockfd,retval;
	socklen_t actuallen;
	int recdbytes,sentbytes;
	struct sockaddr_in serveraddr,clientaddr;
	char buff[MAXSIZE];
	bool file_found=false;
	int count=0;
	char str[MAXSIZE];
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
	
	recdbytes=recv(newsockfd,buff,sizeof(buff),0);

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

	count = store_strings(file, str);
	sort(str, count);
	puts(str);
	recdbytes=recv(newsockfd,buff,sizeof(buff),0);
	sentbytes=send(newsockfd,str,sizeof(str),0);
	//sort(str, count);

	close(sockfd);
	close(newsockfd);

}