#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <arpa/inet.h>
#include <cstdlib>
#include <sys/socket.h>
#include <cerrno>
#include <cstdio>
#include <unistd.h>
#include <cstring>
const int BUFSIZE = 256;

class Client
{
	int fd, status;
	
	ssize_t bytes_num;

	char buffer[BUFSIZE];
	struct sockaddr_in addr;

	void init();
	void connect_sock();

public:
	void running();

	Client();
	~Client();
};

#endif