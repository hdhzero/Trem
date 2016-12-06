#include "socket.h"

Socket::Socket() {
    memset(this, 0, sizeof(*this));
}

Socket::Socket(char* ip, unsigned short port) {
    memset(this, 0, sizeof(*this));

    descriptor = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    connect(descriptor, (struct sockaddr*) &addr, sizeof(addr));
}

Socket::Socket(unsigned short port) {
    memset(this, 0, sizeof(*this));

    descriptor = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(descriptor, (struct sockaddr*) &addr, sizeof(addr));
    listen(descriptor, 10);
}

Socket::~Socket() {
    close();
}

void Socket::close() {
    ::close(descriptor);
}

Socket Socket::accept() {
    Socket new_socket;

    new_socket.descriptor = ::accept(descriptor, (struct sockaddr*) &addr, &size);
    return new_socket;
}

void Socket::write_byte(unsigned char byte) {
    send(descriptor, &byte, 1, 0);
}

unsigned char Socket::read_byte() {
    unsigned char byte;

    recv(descriptor, &byte, 1, 0);
    return byte;
}
