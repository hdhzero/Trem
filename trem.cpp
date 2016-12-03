#include "trem.h"

Trem::Trem(int id, int x, int y)
{
    this->id = id;
    this->x = x;
    this->y = y;
    velocidade = 30;
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
    bool up_flag = true;

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

        case 3:
            if (enable) {
                emit updateGUI(id,x,y);

                if (x == 242 && y > 193) {
                    y -= 1;
                } else if (y == 193 && x < 341) {
                    x += 1;
                } else if (x == 341 && y < 291) {
                    y += 1;
                } else {
                    x -= 1;
                }
            }

            break;

        case 4:
            if (enable) {
                emit updateGUI(id,x,y);

                if (x == 242 && y > 95 && up_flag) {
                    y -= 1;
                } else if (y == 95 && x > 144) {
                    x-= 1;
                    up_flag = false;
                } else if (x == 144 && y < 291){
                    y += 1;
                } else if (y == 291 && x < 341) {
                    x += 1;
                } else if (x == 341 && y < 390) {
                    y += 1;
                } else {
                    x -= 1;
                    up_flag = true;
                }

            }

            break;

        default:
            break;
        }

        this_thread::sleep_for(chrono::milliseconds(velocidade));
    }
}

