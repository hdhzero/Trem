#ifndef SOCKET_H
#define SOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>

class Socket {
public:
	Socket();
	Socket(unsigned short port);
	Socket(char* ip, unsigned short port);
	~Socket();

public:
	Socket accept();
	void close();
	void write_byte(unsigned char byte);
	unsigned char read_byte();

private:
	int descriptor;
	socklen_t size;
	struct sockaddr_in addr;
};

#endif
