#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#define MAXSIZE 150

struct Books {
    char title[50];
    char author[50];
    int book_id;
}r, s, db[10];



void main()
{
    int sockfd,retval, ch, ch1, i;
    int recedbytes,sentbytes, recans;
    struct sockaddr_in serveraddr;
    char buff[MAXSIZE], title[MAXSIZE];
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
    else{
        do{
            printf("1. Add\n" );
            printf("2. Delete\n" );
            printf("3. Display\n" );
            printf("4. Search\n" );
            printf("5. Exit\n" );

            scanf("%d", &ch);
            sentbytes=send(sockfd,&ch,sizeof(ch),0);
            recedbytes = recv(sockfd,&ch1,sizeof(ch),0);
            switch(ch){

                case 1:
                printf("Id: \n" );
                scanf("%d", &s.book_id);
                printf("Title: \n" );
                scanf("%s", s.title);
                printf("Author: \n" );
                scanf("%s", s.author);
                sentbytes = send(sockfd,&s,sizeof(s),0);
                recedbytes = recv(sockfd,buff,sizeof(buff),0);
                break;
                case 2:
                printf("Enter Title to delete\n");
                scanf("%s", title);
                sentbytes = send(sockfd, title, sizeof(title), 0);
                recedbytes = recv(sockfd, buff, sizeof(buff), 0);
                printf("Deleted\n");
                break;
                case 3:
                recedbytes = recv(sockfd, db, sizeof(db), 0);
                recedbytes = recv(sockfd, &ch1, sizeof(ch), 0);
                printf("===========BOOKS===========\n");
                for(i = 0; i < ch1; i++){
                    printf("ID: %d\n", db[i].book_id);
                    printf("Title: %s\n", db[i].title);
                    printf("Author %s\n", db[i].author);
                    printf("-------------------------\n");
                }
                break;
                case 4:
                printf("Enter Title to search\n");
                scanf("%s", title);
                sentbytes = send(sockfd, title, sizeof(title), 0);
                recedbytes = recv(sockfd, &r, sizeof(r), 0);
                if(strcmp(r.title, "NULL") == 0)
                    printf("No such book");
                else{
                    printf("ID: %d\n", r.book_id);
                    printf("Title: %s\n", r.title);
                    printf("Author: %s\n", r.author);
                }
                break;
            }
        
        }while(ch != 5);
    }
}
