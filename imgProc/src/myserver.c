#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *message)
{
	perror(message);
	exit(0);
}

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, port_no, n;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	FILE *f;

	if(argc < 2)
	{
		fprintf(stderr, "Error, no port provided.\n");
		exit(0);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		error("Error opening socket.");
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	port_no = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port_no);
	if(bind(sockfd,(struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
	{
		error("Error on binding.");
	}
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);
	if(newsockfd < 0)
	{
		error("Error on accept.");
	}
	/*

	while(1)
	{
		bzero(buffer,256);
		n = read(newsockfd,buffer,255);
		if(n < 0)
			error("Error reading from socket.");
		printf("Message: %s", buffer);
		n = write(newsockfd,"OK",2);
		if(n < 0)
			error("Error writing to socket.");
	}
	*/
	f = fopen("in.txt","rb");

	while(!feof(f))
	{
		bzero(buffer,256);
		fread(buffer,sizeof(buffer),1,f);
		puts(buffer);
		n = write(newsockfd,buffer,256);
		if(n < 0)
		{
			error("Server -> Error writing to socket.");
		}
	}
	fclose(f);

	close(newsockfd);
	close(sockfd);
	return 0;
}