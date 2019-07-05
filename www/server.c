#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

#define BUF_SIZE 256

void commun(int);
void DieWithError(char *);
int main(int argc,char** argv)
{
	
	int cliSock;
	int servSock = socket(PF_INET,SOCK_STREAM,0);
	struct sockaddr_in servAddress;
	struct sockaddr_in clientAddress;
	socklen_t szClientAddr;
	servAddress.sin_family		 = AF_INET;
	servAddress.sin_addr.s_addr	 = htonl(INADDR_ANY);
	servAddress.sin_port		 = htons(80);
	
	bind(servSock, (struct sockaddr *) & servAddress, sizeof(servAddress));
	
	listen(servSock,5);
	while(1)
	{
		szClientAddr = sizeof(clientAddress);
		cliSock		 = accept(servSock,(struct sockaddr *)&clientAddress,&szClientAddr);
		
		/*--------------------*/
		/*		í êMäJén	  */
		/*--------------------*/
		
		commun(cliSock);
		close(servSock);
	}
	close(servSock);
	return 0;
}

void DieWithError(char *errorMessage)
{
	perror(errorMessage);
	exit(1);
}
void commun(int sock)
{
	char buf[BUF_SIZE];
	char buf2[BUF_SIZE * 2];
	char buf_old[BUF_SIZE];
	int len_r;
	char response[BUF_SIZE];
	
	buf_old[0] = '/0';

	while(0 < (len_r=recv(sock,buf,BUF_SIZE,0)))
	{
		buf[len_r]='\0';
		sprintf(buf2, "%s%s", buf_old, buf);
		
		//printf("%s\n",buf);
		/*if(strstr(buf, "\r\n\r\n"))
		{
			break;
		}*/
		
		if(strstr(buf2, "\r\n\r\n"))
		{
			break;
		}
		
		sprintf(buf_old, "%s", buf);
	}
	
	printf("kaigyou futatu atta yo");
	
	if(len_r <= 0)
	{
		DieWithError("recv()failed");
	}
	
	printf("%s\n",buf);
	
	sprintf(response, "HTTP/1.1 200 OK\r\n");
	
	if(send(sock,response,strlen(response),0)!=strlen(response))
	{
		DieWithError("send() sent amessage of unexpected bytes");
	}
}
