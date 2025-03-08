#ifndef SERVER_HPP
#define SERVER_HPP

#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <csignal>
const unsigned BUFFER_SIZE = 1024;

class Server
{
	int status;
	int fd, client;
	sockaddr_in addr;
	char buffer[BUFFER_SIZE];

	char host[NI_MAXHOST], service[NI_MAXSERV];
	socklen_t addr_len;

	void init();
	void sock_listen();
	void connect();
	void sock_bind();
	void sock_accept();
public:
	
	void running();
	void closing(int);

	Server();
	~Server();
};

#endif