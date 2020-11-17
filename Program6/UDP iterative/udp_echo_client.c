/*Client*/
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include<errno.h>

#define SERV_PORT 9002
#define MAXLINE 1024
/*void dg_cli(FILE *fp, int sockfd,struct sockaddr* serv_address, int servlen)
{
   int bufsize = 1024, cont;
   char *buffer = malloc(bufsize);
	int addrlen = sizeof(struct sockaddr_in);
	while(fgets(buffer,bufsize,fp)!=NULL){
	if ((strncmp(buffer, "exit", 4)) == 0)
	{
	printf("Client Exit...\n");
	
	break;
	}
	
	sendto(sockfd, buffer, sizeof(buffer),0,serv_address,servlen);  

  	if((cont=recvfrom(sockfd, buffer, bufsize, 0,NULL,NULL)>0)) 
	{
    	fputs(buffer,stdout);		//echo printing
  	}}
	
  printf("\nEOF\n");
}*/
void dg_cli(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen)
{

	int n;

	char sendline[MAXLINE], recvline[MAXLINE];

	while (fgets(sendline, MAXLINE, fp) != NULL) {
		sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
		if ((strncmp(sendline, "exit", 4)) == 0)
	{
	printf("Client Exit...\n");
	
	break;
	}
		n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
 
		recvline[n] = '\0';
		/* null terminate */
		fputs(recvline, stdout);
		
	}
}
int main(int argc,char *argv[])
{
  int sockfd;
  
  //char fname[256];
  struct sockaddr_in serv_address;
  if ((sockfd = socket(AF_INET,SOCK_DGRAM,0)) > 0)
  printf("The Socket was created\n");
  serv_address.sin_family = AF_INET;
  serv_address.sin_port = htons(16001);

  inet_pton(AF_INET,argv[1],&serv_address.sin_addr);
 
  
  dg_cli(stdin,sockfd,(struct sockaddr *)&serv_address,sizeof(serv_address));


  exit(0);
}

