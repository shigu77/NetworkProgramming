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
		/*		�ʐM�J�n	  */
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
	int len_r;
	char response[BUF_SIZE];
	
	while(0 < (len_r=recv(sock,buf,BUF_SIZE,0)))
	{
		buf[len_r]='\0';
		printf("%s\n",buf);
		if(strstr(buf, "\r\n\r\n"))
		{
			break;
		}
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
