#include "trem.h"

Trem::Trem(int id, int x, int y, QMutex* trilhos) {
    for (int i = 0; i < 32; ++i) {
        speed_table[i] = i / 31.0;
    }

    this->id = id;
    this->x = x;
    this->y = y;
    velocidade = 3;
    speed = speed_table[7];
    enable = true;
    this->trilhos = trilhos;
}

Trem::~Trem() {
    threadTrem.join();
}

void Trem::setSpeed(int speed) {
    this->speed = speed_table[speed];
}

void Trem::setEnable(bool enable) {
    this->enable = enable;
}

void Trem::start() {
    threadTrem = std::thread(&Trem::run,this);
}

void Trem::walk(int& var, int limit, bool inc) {
    float var_aux = var;

    if (inc) {
        while (var < limit) {
            emit updateGUI(id, x, y);

            if (enable) {
                var_aux += speed;
                var = var_aux;
            }

            this_thread::sleep_for(chrono::milliseconds(velocidade));
        }
    } else {
        while (var > limit) {
            emit updateGUI(id, x, y);

            if (enable) {
                var_aux -= speed;
                var = var_aux;
            }

            this_thread::sleep_for(chrono::milliseconds(velocidade));
        }
    }
}

void Trem::run() {
    bool up_flag = true;
    const int TLIMIT = 17;

    while(true){
        switch(id){
        case 1:
            if (y == 95 && x > 144) {
                walk(x, 242 - TLIMIT, false);
                trilhos[5].unlock();
                walk(x, 144 + TLIMIT, false);
                trilhos[0].lock();
                walk(x, 144, false);
            } else if (x == 144 && y < 193) {
                walk(y, 95 + TLIMIT, true);
                trilhos[2].unlock();
                walk(y, 193 - TLIMIT, true);
                trilhos[3].lock();
                walk(y, 193, true);
            } else if (y == 193 && x < 242) {
                walk(x, 144 + TLIMIT, true);
                trilhos[0].unlock();
                walk(x, 242 - TLIMIT, true);
                trilhos[5].lock();
                trilhos[8].lock();
                walk(x, 242, true);
            } else {
                walk(y, 193 - TLIMIT, false);
                trilhos[3].unlock();
                trilhos[8].unlock();
                walk(y, 95 + TLIMIT, false);
                trilhos[2].lock();
                walk(y, 95, false);
            }

            break;

        case 2:
            if (x == 144 && y > 193) {
                walk(y, 193 + TLIMIT, false);
                trilhos[3].lock();
                walk(y, 193, false);
            } else if (y == 193 && x < 242) {
                walk(x, 144 + TLIMIT, true);
                trilhos[1].unlock();
                trilhos[4].unlock();
                walk(x, 242 - TLIMIT, true);
                trilhos[6].lock();
                walk(x, 242, true);
            } else if (x == 242 && y < 291) {
                walk(y, 193 + TLIMIT, true);
                trilhos[3].unlock();
                walk(y, 291 - TLIMIT, true);
                trilhos[1].lock();
                trilhos[4].lock();
                walk(y, 291, true);
            } else {
                walk(x, 242 - TLIMIT, false);
                trilhos[6].unlock();
                walk(x, 144, false);
            }

            break;

        case 3:
            if (x == 242 && y > 193) {
                walk(y, 291 - TLIMIT, false);
                trilhos[9].unlock();
                walk(y, 193 + TLIMIT, false);
                trilhos[8].lock();
                walk(y, 193, false);
            } else if (y == 193 && x < 341) {
                walk(x, 242 + TLIMIT, true);
                trilhos[6].unlock();
                trilhos[8].unlock();
                walk(x, 341 - TLIMIT, true);
                trilhos[11].lock();
                walk(x, 341, true);
            } else if (x == 341 && y < 291) {
                walk(y, 291 - TLIMIT, true);
                trilhos[9].lock();
                walk(y, 291, true);
            } else {
                walk(x, 341 - TLIMIT, false);
                trilhos[11].unlock();
                walk(x, 242 + TLIMIT, false);
                trilhos[6].lock();
                walk(x, 242, false);
            }

            break;

        case 4:
            if (x == 242 && y > 291 && up_flag) {
                walk(y, 291 + TLIMIT, false);
                trilhos[6].lock();
                walk(y, 291, false);
            } else if (x == 242 && y > 193 && up_flag) {
                walk(y, 193  + TLIMIT, false);
                trilhos[5].lock();
                walk(y, 193, false);
            } else if (x == 242 && y > 95 && up_flag) {
                walk(y, 193 - TLIMIT, false);
                trilhos[6].unlock();
                walk(y, 95 + TLIMIT, false);
                trilhos[2].lock();
                walk(y, 95, false);
            } else if (y == 95 && x > 144) {
                walk(x, 242 - TLIMIT, false);
                trilhos[5].unlock();
                walk(x, 144 + TLIMIT, false);
                trilhos[0].lock();
                walk(x, 144, false);
                up_flag = false;
            } else if (x == 144 && y < 193) {
                walk(y, 95 + TLIMIT, true);
                trilhos[2].unlock();
                walk(y, 193 - TLIMIT, true);
                trilhos[1].lock();
                trilhos[4].lock();
                trilhos[9].lock();
                walk(y, 193, true);
            } else if (x == 144 && y < 291) {
                walk(y, 193 + TLIMIT, true);
                trilhos[0].unlock();
                walk(y, 291, true);
            } else if (y == 291 && x < 242) {
                walk(x, 242, true);
            } else if (y == 291 && x < 341) {
                walk(x, 242 + TLIMIT, true);
                trilhos[1].unlock();
                trilhos[4].unlock();
                walk(x, 341, true);
            } else if (x == 341 && y < 390) {
                walk(y, 291 + TLIMIT, true);
                trilhos[9].unlock();
                walk(y, 390, true);
            } else {
                walk(x, 242, false);
                up_flag = true;
            }

            break;

        default:
            break;
        }

        this_thread::sleep_for(chrono::milliseconds(velocidade));
    }
}
