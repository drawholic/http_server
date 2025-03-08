#include "Server.hpp"


Server::Server()
{
	init();
	sock_bind();
	sock_listen(); 
};

Server::~Server()
{
	close(fd);
};

void Server::init()
{

	fd = socket(AF_INET, SOCK_STREAM, 0);

	if(fd == -1)
	{
		perror("Failure creating socket");
		exit(EXIT_FAILURE);
	};


	int reuse = 1;
	status = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
	if(status < 0)
	{
		perror("Failure setting option");
		close(fd);
		exit(EXIT_FAILURE);
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(8000);
	addr.sin_addr.s_addr = INADDR_ANY;

	addr_len = sizeof(addr);

};


void Server::sock_bind()
{
	status = bind(fd, (sockaddr*)&addr, sizeof(addr));
	
	if(status == -1)
	{
		perror("Failure on binding");
		exit(EXIT_FAILURE);
	};
};

void Server::sock_listen()
{
	status = listen(fd, 10);

	if(status == -1)
	{
		perror("Failure on listeing");
		exit(EXIT_FAILURE);
	};
};

void Server::sock_accept()
{

	client = accept(fd, (sockaddr*)&addr, &addr_len);

	if(client  == -1)
	{
		perror("Failure accepting");
		close(client);
		return;
	};

	int bytes_read;

	bytes_read = recv(client, buffer, BUFFER_SIZE, 0);
	if(bytes_read == -1)
	{
		perror("Failure receiving");
		close(client);
		return;
	};
	buffer[bytes_read] = 0;
	printf("%s\n", buffer);
	
	const char* msg = "hello";
	bytes_read = send(client, msg, strlen(msg),0);
	if(bytes_read != strlen(msg))
	{
		perror("Failure sending");
	};
	close(client);
};


void Server::running()
{
	if(getnameinfo(
		(sockaddr*)&addr, 
		addr_len, 
		host, 
		sizeof(host), 
		service, 
		sizeof(service), 
		NI_NUMERICHOST | NI_NUMERICSERV)
		 == 0)
	printf("Running at %s, service %s\n", host, service);

	sock_accept();

};


void Server::closing(int sig)
{
	printf("Closing server...\n");
	close(fd);
};

void Server::connect(){};