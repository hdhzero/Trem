#include "trem.h"

Trem::Trem(int id, int x, int y, QMutex* trilhos) {
    this->id = id;
    this->x = x;
    this->y = y;
    velocidade = 5;
    speed = 1.0;
    enable = true;
    this->trilhos = trilhos;

    if (id == 2) {
        trilhos[1].lock();
    }

    for (int i = 0; i < 32; ++i) {
        speed_table[i] = 1.0 - (1.0 / 32.0) * (31 - i);
    }
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

    while(true){
        switch(id){
        case 1:
            if (y == 95 && x > 144) {
                trilhos[2].lock();
                walk(x, 144, false);
                trilhos[2].unlock();
            } else if (x == 144 && y < 193) {
                trilhos[0].lock();
                walk(y, 193, true);
                trilhos[0].unlock();
            } else if (y == 193 && x < 242) {
                trilhos[3].lock();
                walk(x, 242, true);
                trilhos[3].unlock();
            } else {
                trilhos[5].lock();
                walk(y, 95, false);
                trilhos[5].unlock();
            }

            break;

        case 2:
            if (x == 144 && y > 193) {
                walk(y, 193, false);
                trilhos[1].unlock();
            } else if (y == 193 && x < 242) {
                trilhos[3].lock();
                walk(x, 242, true);
                trilhos[3].unlock();
            } else if (x == 242 && y < 291) {
                trilhos[6].lock();
                walk(y, 291, true);
                trilhos[6].unlock();
            } else {
                trilhos[1].lock();
                walk(x, 144, false);
            }

            break;

        case 3:
            if (x == 242 && y > 193) {
                trilhos[6].lock();
                walk(y, 193, false);
                trilhos[6].unlock();
            } else if (y == 193 && x < 341) {
                trilhos[8].lock();
                walk(x, 341, true);
                trilhos[8].unlock();
            } else if (x == 341 && y < 291) {
                trilhos[11].lock();
                walk(y, 291, true);
                trilhos[11].unlock();
            } else {
                trilhos[9].lock();
                walk(x, 242, false);
                trilhos[9].unlock();
            }

            break;

        case 4:
            if (x == 242 && y > 291 && up_flag) {
                trilhos[7].lock();
                walk(y, 291, false);
                trilhos[7].unlock();
            } else if (x == 242 && y > 193 && up_flag) {
                trilhos[6].lock();
                walk(y, 193, false);
                trilhos[6].unlock();
            } else if (x == 242 && y > 95 && up_flag) {
                trilhos[5].lock();
                walk(y, 95, false);
                trilhos[5].unlock();
            } else if (y == 95 && x > 144) {
                trilhos[2].lock();
                walk(x, 144, false);
                trilhos[2].unlock();
                up_flag = false;
            } else if (x == 144 && y < 193) {
                trilhos[0].lock();
                walk(y, 193, true);
                trilhos[0].unlock();
            } else if (x == 144 && y < 291) {
                trilhos[1].lock();
                walk(y, 291, true);
            } else if (y == 291 && x < 242) {
                walk(x, 242, true);
                trilhos[1].unlock();
            } else if (y == 291 && x < 341) {
                trilhos[9].lock();
                walk(x, 341, true);
                trilhos[9].unlock();
            } else if (x == 341 && y < 390) {
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
