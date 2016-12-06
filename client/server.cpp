#include "Socket.h"

int main() {
	Socket sock(7070);
	Socket cli;
	unsigned char byte;
	unsigned char counter = '0';

	while (1) {
		Socket cli = sock.accept();

		byte = cli.read_byte();
		printf("received: %c\n", byte);
		cli.write_byte(counter++);
	}

	return 0;

}
