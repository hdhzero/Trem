#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <QObject>
#include <thread>
#include <chrono>
#include "trem.h"
#include "socket.h"
using namespace std;

class Servidor : public QObject {
    Q_OBJECT

public:
    Servidor(int);
    ~Servidor();
    void start();
    void run();
    void addTrem(Trem* trem, int id);

private:
    Trem* trens[4];
    std::thread threadServidor;
    Socket sock;
};

#endif // SERVIDOR_H
