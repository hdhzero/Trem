#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <thread>
#include <chrono>
#include "trem.h"
using namespace std;

class Servidor : public QObject {
    Q_OBJECT

public:
    Servidor(int);
    ~Servidor();
    void start();
    void run();
    void addTrem(Trem* trem, int id);

signals:
    void updateGUI(int,int,int);

private:
    Trem* trens[4];
    std::thread threadServidor;
    QTcpSocket socket;
    int port;
};

#endif // SERVIDOR_H
