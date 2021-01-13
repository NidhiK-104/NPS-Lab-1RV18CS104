#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include<stdlib.h>
#define HELLO_PORT 12345
#define HELLO_GROUP "225.0.0.37"
#define MSGBUFSIZE 1024000
int main(int argc, char *argv[])
{
struct sockaddr_in addr;
int fd, nbytes,addrlen,ml;
struct ip_mreq mreq;
char msgbuf[MSGBUFSIZE];
u_int yes=1; /*** MODIFICATION TO ORIGINAL */
/* create what looks like an ordinary UDP socket */
if ((fd=socket(AF_INET,SOCK_DGRAM,0)) < 0) {
perror("Opening datagram socket error");
exit(1);
}
else
        printf("Opening datagram socket....OK.\n");
/**** MODIFICATION TO ORIGINAL */
/* allow multiple sockets to use the same PORT number */
if (setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)) < 0) {
perror("Reusing ADDR failed");
exit(1);
}
else
        printf("Reusing ADDR...OK.\n");

/*** END OF MODIFICATION TO ORIGINAL */
/* set up destination address */
bzero(&addr,sizeof(addr));
addr.sin_family=AF_INET;
addr.sin_addr.s_addr=htonl(INADDR_ANY); /* N.B.: differs from sender*/
addr.sin_port=htons(HELLO_PORT);
/* bind to receive address */
if (bind(fd,(struct sockaddr *) &addr,sizeof(addr)) < 0) {
perror("bind");
exit(1);
}
else
        printf("Binding datagram socket...OK.\n");
/* use setsockopt() to request that the kernel join a multicast
group */
mreq.imr_multiaddr.s_addr=inet_addr(HELLO_GROUP);
mreq.imr_interface.s_addr=htonl(INADDR_ANY);
if (setsockopt(fd,IPPROTO_IP,IP_ADD_MEMBERSHIP,(char *) &mreq,sizeof(mreq)) < 0) {
perror("Adding multicast group error");
exit(1);
}
else
    printf("Adding multicast group...OK.\n");
/* now just enter a read-print loop */
ml=sizeof(msgbuf);
while (1) {
//addrlen=sizeof(addr);

//if ((nbytes=recvfrom(fd,msgbuf,ml,0, (struct sockaddr *) &addr,&addrlen)) < 0) {
if ((nbytes=recvfrom(fd,msgbuf,sizeof(msgbuf),0, NULL, NULL) )< 0) {
perror("Reading datagram message error");
exit(0);
}
//msgbuf[nbytes]='\0';

printf("The message from multicast server is: %s \n", msgbuf);
//printf("%d\n",strlen(msgbuf));
//puts(msgbuf);
}
}

