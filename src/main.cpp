
#include "Server.hpp"
#include <csignal>

 
Server s;

void handle_interrupt(int);

int main(int argc, char const *argv[])
{
	signal(SIGINT, handle_interrupt);
	s.running();
	return 0;
}


void handle_interrupt(int sig)
{
	printf("Interrupting...\n");
	s.closing(sig);
	exit(EXIT_SUCCESS);
};