#include "servidor.h"

Servidor::Servidor(int port) : sock(port) {

}

Servidor::~Servidor() {
    threadServidor.join();
}

void Servidor::start() {
    threadServidor = std::thread(&Servidor::run, this);
}

void Servidor::run() {
    int trem;
    bool enable;
    int speed;

    while (true) {
        Socket cli = sock.accept();

        unsigned char cmd = cli.read_byte();
        printf("Received: %i\n", (int) cmd);

        if (cmd == 0 || cmd == 1) {
            trens[0]->setEnable(cmd == 1);
            trens[1]->setEnable(cmd == 1);
            trens[2]->setEnable(cmd == 1);
            trens[3]->setEnable(cmd == 1);
        } else if (cmd & 0x08) {
            trem = (cmd  >> 1) & 0x03;
            enable = cmd & 0x01;
            trens[trem]->setEnable(enable);
        } else if (cmd & 0x80) {
            trem = (cmd >> 5) & 0x03;
            speed = cmd & 0x1f;
            trens[trem]->setSpeed(speed);
        } else if (cmd == 2) {
            for (int k = 0; k < 4; ++k) {
                cmd = (trens[k]->getEnable() << 5) | (trens[k]->getSpeed() & 31);
                cli.write_byte(cmd);
            }
        }
    }
}

void Servidor::addTrem(Trem *trem, int id) {
    trens[id - 1] = trem;
}
