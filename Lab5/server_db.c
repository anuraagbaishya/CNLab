#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAXSIZE 150

int flag = 0;

struct Books {
    char title[50];
    char author[50];
    int book_id;
}r, s, db[10], db_bak[10];

void main()
{
    int sockfd,newsockfd,retval, ch, i, j = 0, count = 0, flag = 0;
    socklen_t actuallen;
    int recedbytes,sentbytes, sentans;
    struct sockaddr_in serveraddr,clientaddr;

    char buff[MAXSIZE], temp[MAXSIZE];
    strcpy(buff, "Success");
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
    do{
        recedbytes = recv(newsockfd,&ch,sizeof(ch),0);
        sentbytes = send(newsockfd,&ch,sizeof(ch),0);

        switch(ch){

            case 1:
            recedbytes = recv(newsockfd,&r,sizeof(r),0);
            db[count++] = r;
            printf("%s\n", r.title);
            printf("%s\n", r.author);
            printf("%d\n", r.book_id);
            sentbytes = send(newsockfd,buff,sizeof(buff),0);
            break;
            case 2:
            recedbytes = recv(newsockfd,temp,sizeof(temp),0);
            for(i = 0; i < count; i++){

                if(strcmp(db[i].title, temp) == 0)
                    continue;
                db_bak[j++] = db[i];
                count--;
            }
            for(i = 0; i < count; i++)
                db[i] = db_bak[i];
            sentbytes = send(newsockfd,buff,sizeof(buff),0);
            break;
            case 3:
            //recedbytes = recv(newsockfd,temp,sizeof(temp),0);
            sentbytes = send(newsockfd, db, sizeof(db), 0);
            sentbytes = send(newsockfd, &count, sizeof(count), 0); 
            break;
            case 4:
            recedbytes = recv(newsockfd,temp,sizeof(temp),0);
            for(i = 0; i < count; i++){
                if(strcmp(db[i].title, temp) == 0){
                    s = db[i];
                    sentbytes = send(newsockfd, &s, sizeof(s), 0);
                    flag = 1;
                }
            }
            if(flag == 0){
                struct Books book;
                strcpy(book.title, "NULL");
                strcpy(book.author, "NULL");
                book.book_id = 0;
                sentbytes = send(newsockfd, &book, sizeof(book), 0);
            }
            break;
        }
        
   }while(strcmp(buff, "stop") != 0);
    
}

