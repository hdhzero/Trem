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
    void setEnable(bool);
    int getEnable();
    void setSpeed(int);
    int getSpeed();

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
   float speed;
   int speed_index;
   bool enable;
   QMutex* trilhos;
   float speed_table[32];
};

#endif // TREM_H



