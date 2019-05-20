/*

i got a lot of the original framework for the nonblocking networking for this client
somewhere online but i can't find the website i originally got it from

*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include "client.h"
#include "../gfx/GUI.h"

#define PORT 10000    /* the port client will be connecting to */

#define MAXDATASIZE 1024 /* max number of bytes we can get at once */

static int shutDown;
char* sendText;
static int sendReady;

Client * newClient() {
    return (Client *) malloc(sizeof(Client));
}

void initClient(Client * me, ReplyHandler* rh, int assign) {
    printf("initClient\n");
    me->id=malloc(sizeof(int));
    *(me->id) = assign;
    sendText = malloc(sizeof(char)*1024);
    sendReady=0;
    me->replyHandler = rh;
}

void shutDownClient() {
    shutDown=1;
}


void * startClient(void * arg) {
    Client * c = (Client*)arg;
    shutDown = 0;
    printf("startClient called\n");
    //Client * me = (Client *) arg;
    int sockfd, numbytes;
    char sendbuf[MAXDATASIZE];
    char recvbuf[MAXDATASIZE];
    int curBufSize=0;
    struct hostent *he;
    struct sockaddr_in their_addr; /* connector's address information */

    char * hostname = "127.0.0.1";

    if ((he=gethostbyname(hostname)) == NULL) {  /* get the host info */
        herror("gethostbyname");
        exit(1);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
    their_addr.sin_family = AF_INET;      /* host byte order */
    their_addr.sin_port = htons(PORT);    /* short, network byte order */
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    bzero(&(their_addr.sin_zero), 8);     /* zero the rest of the struct */

    if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1) {
        printf("error connecting to server - possibly offline\n"); //i had to add this message cuz i kept trying to test my client while the server wasn't running and getting really frustrated with this error
        perror("connect");
        exit(1);
    }
        /* sleep(5); */
        int k=0;
	while (shutDown!=1){

        /*if ((k)<50) {
		    if (send(sockfd, "Hello, world!\n", 14, MSG_DONTWAIT) == -1)
		        perror("send error");
            printf("sent a message %d",k);
            k++;
        }*/
        if (sendReady) {
            //printf("gonna send this: {%s}\n",sendText);
            //printf("strlen is %lu\n",strlen(sendText));
            strcpy(sendbuf,sendText);
            //printf("sendtext: %s",sendText);
            //printf("sendbuf: %s",sendbuf);
            //memset(recvbuf, 0, sizeof(recvbuf));
            //char * sendThis = malloc(sizeof(char)*(strlen(sendText)));
            //strcpy(sendThis,sendText);
            if (send(sockfd,sendbuf,sizeof(sendbuf),MSG_DONTWAIT)==-1) //HA I FINALLY GOT IT
                perror("send error");
            else {
                printf("sent {%s}\n",sendText);
            }
            sendReady=0;
            memset(sendbuf, 0, sizeof(sendbuf));
            //printf("sendtext: %s",sendText);
            //printf("sendbuf: %s",sendbuf);
            //free(sendThis);
            //*sendText = '\0';
        }
        //handle incoming messages
        if (recv(sockfd, recvbuf,sizeof(recvbuf),MSG_DONTWAIT) != -1) {
            if (strlen(recvbuf)>0)
                printf("<newmsg>%s</newmsg>\n",recvbuf);
            handleReply(c->replyHandler,recvbuf);
            //clearBuffer(recvbuf);
            memset(recvbuf,0,sizeof(recvbuf));
        }
        else {
            //no data to read - do nothing
        }
	}
        close(sockfd);
        free(c->id);
        free(c);

        return NULL;
}


void sendMessage(char* send) {
    sendText = send;
    sendReady = 1;
}
