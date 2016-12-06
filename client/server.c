#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>

typedef struct Socket {
	int descriptor;
	int size;
	struct sockaddr_in addr;
} Socket;

Socket* socket_new(char* ip, unsigned short port) {
	Socket* new_socket;

	new_socket = malloc(sizeof(Socket));
	memset(new_socket, 0, sizeof(Socket));

	new_socket->descriptor = socket(AF_INET, SOCK_STREAM, 0);

	new_socket->addr.sin_family = AF_INET;
	new_socket->addr.sin_port = htons(port);
	new_socket->addr.sin_addr.s_addr = inet_addr(ip);

	connect(new_socket->descriptor, (struct sockaddr*) &new_socket->addr, sizeof(new_socket->addr));
	return new_socket;
}

Socket* socket_server_new(unsigned short port) {
	Socket* new_socket;

	new_socket = malloc(sizeof(Socket));
	memset(new_socket, 0, sizeof(Socket));

	new_socket->descriptor = socket(AF_INET, SOCK_STREAM, 0);
	new_socket->addr.sin_family = AF_INET;
	new_socket->addr.sin_port = htons(port);
	new_socket->addr.sin_addr.s_addr = INADDR_ANY; 

	bind(new_socket->descriptor, (struct sockaddr*) &new_socket->addr, sizeof(new_socket->addr));
	listen(new_socket->descriptor, 10);

	return new_socket;
}

Socket* socket_accept(Socket* sock) {
	Socket* new_socket;

	new_socket = malloc(sizeof(Socket));
	memset(new_socket, 0, sizeof(Socket));

	new_socket->descriptor = accept(sock->descriptor, (struct sockaddr*) &new_socket->addr, &new_socket->size);
	return new_socket;
}

void socket_destroy(Socket* sock) {
	close(sock->descriptor);
	free(sock);
}

void socket_write_byte(Socket* sock, unsigned char byte) {
	send(sock->descriptor, &byte, 1, 0);
}

unsigned char socket_read_byte(Socket* sock) {
	unsigned char byte;

	recv(sock->descriptor, &byte, 1, 0);
	return byte;
}

/* Formato dos pacotes 
 * 	00000000 - desliga todos os trens
 *	00000001 - liga todos os trens
 *	00000xyp - p = 1 liga o trem xy; p = 0 desliga o trem xy
 *	1xyvvvvv - seta a velocidade do trem xy, com a velocidade variando de 0 a 31
 */
int main(int argc, char* argv) {
	Socket* sock;
	Socket* cli;
	unsigned char byte;
	unsigned char counter = '0';

	sock = socket_server_new(7007);

	while (1) {
		cli = socket_accept(sock);

		byte = socket_read_byte(cli);
		printf("received: %c\n", byte);
		socket_write_byte(cli, counter++);
		socket_destroy(cli);
	}

	return 0;
	
}
