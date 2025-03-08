#include "Client.hpp"

Client::Client()
{
	init();
	connect_sock();
};

Client::~Client()
{
	close(fd);
};

void Client::init()
{
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if(fd == -1)
	{
		perror("Error creating socket");
		exit(EXIT_FAILURE);
	};

	// addr.sin_addr.s_addr = INADDR_ANY;
	inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
	addr.sin_port = htons(8000);
	addr.sin_family = AF_INET;
};
 

void Client::connect_sock()
{
	status = connect(fd, (sockaddr*)&addr, sizeof(addr));
	if(status == -1)
	{
		perror("Failure connecting");
		close(fd);
		exit(EXIT_FAILURE);
	};
};

void Client::running()
{
	const char*msg = "hello server";
	unsigned msgLen = strlen(msg);
	
	bytes_num = send(fd, msg, msgLen, 0);
	
	if(bytes_num != msgLen)
	{
		perror("Failure sending");
		close(fd);
		exit(EXIT_FAILURE);
	};
	
	while((bytes_num = recv(fd, buffer, BUFSIZE - 1, 0)) > 0 )
	{
		buffer[bytes_num] = 0;
		printf("Received: %s\n", buffer);
	}
	if(bytes_num == -1)
	{
		perror("Failure receiving");
		close(fd);
		exit(EXIT_FAILURE);
	};

};