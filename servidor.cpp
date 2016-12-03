#include "servidor.h"

Servidor::Servidor(int port) {
    this->port = port;
}

Servidor::~Servidor() {
    threadServidor.join();
}

void Servidor::start() {
    threadServidor = std::thread(&Servidor::run, this);
}

void Servidor::run() {

}

void Servidor::addTrem(Trem *trem, int id) {
    trens[id - 1] = trem;
}
