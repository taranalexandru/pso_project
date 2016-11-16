#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *message)
{
	perror(message);
	exit(0);
}

int main(int argc, char *argv[])
{
	int sockfd, port_no, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	FILE *f;

	char buffer[256];
	if(argc < 3)
	{
		fprintf(stderr,"usage %s: [hostname] [port]\n",argv[0]);
		exit(0);
	}

	port_no = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		error("Error opening socket!");
	}

	server = gethostbyname(argv[1]);
	if(server == NULL)
	{
		fprintf(stderr,"Error, no such host\n");
		exit(0);
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
		(char *) &serv_addr.sin_addr.s_addr,
		server->h_length);
	serv_addr.sin_port = htons(port_no);
	if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		error("Error connecting.");
	}

	/*
	while(1)
	{
		printf("Message: ");
		bzero(buffer,256);
		fgets(buffer,255,stdin);
		n = write(sockfd,buffer,strlen(buffer));
		if(n < 0)
		{
			error("Error writing to socket.");
		}
		bzero(buffer,256);
		n = read(sockfd,buffer,255);
		if(n < 0)
		{
			error("Error reading from socket.");
		}
		printf("%s\n", buffer);
	}
	*/

	f = fopen("out.txt","wb");
	n = 1;
	while(n)
	{
		bzero(buffer,256);
		n = read(sockfd,buffer,255);
		if(n < 0)
			error("Client -> Error reading from socket.");
		printf("%s/n",buffer);
		//fwrite(buffer,1,sizeof(buffer),f);
		fputs(buffer,f);
	}
	fclose(f);

	close(sockfd);
	return 0;
}