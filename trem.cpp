#include "trem.h"

Trem::Trem(int id, int x, int y)
{
    this->id = id;
    this->x = x;
    this->y = y;
    velocidade = 70;
    enable = true;
}

Trem::~Trem()
{
    threadTrem.join();
}

void Trem::setVelocidade(int velocidade)
{
    this->velocidade = velocidade;
}

void Trem::setEnable(bool enable)
{
    this->enable = enable;
}

void Trem::start()
{
    threadTrem = std::thread(&Trem::run,this);
}

void Trem::run()
{
    while(true){
        switch(id){
        case 1:
            if (enable)
            {
                emit updateGUI(id,x,y);

                if (y == 95 && x > 144)
                    x -= 1;
                else if (x == 144 && y < 193)
                    y += 1;
                else if (y == 193 && x < 242)
                    x += 1;
                else
                    y -= 1;
            }
            break;
        case 2:
            if (enable) {
                emit updateGUI(id,x,y);

                if (x == 144 && y > 193) {
                    y -= 1;
                } else if (y == 193 && x < 242) {
                    x += 1;
                } else if (x == 242 && y < 291) {
                    y += 1;
                } else {
                    x -= 1;
                }
            }

            break;
        default:
            break;
        }
        this_thread::sleep_for(chrono::milliseconds(velocidade));
    }
}

