#ifndef TREM_H
#define TREM_H

#include <QObject>
#include <QMutex>
#include <thread>
#include <chrono>
using namespace std;

class Trem : public QObject
{
    Q_OBJECT
public:
    Trem(int,int,int, QMutex*);
    ~Trem();
    void start();
    void run();
    void setVelocidade(int);
    void setEnable(bool);

signals:
    void updateGUI(int,int,int);

private:
    void walk(int& var, int limit, bool inc);

private:
   std::thread threadTrem;
   int id;
   int x;
   int y;
   int velocidade;
   bool enable;
   QMutex* trilhos;
};

#endif // TREM_H



