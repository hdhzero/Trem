#include "Socket.h"
#include <ncurses.h>

bool servidor_conectado = false;
int ligado[4] = {0, 0, 1, 0};
int velocidades[4] = {17, 0, 0, 0};
int opcao = 0;
char* nomes[] = {"amarelo", "vermelho", "azul", "preto"};
char ip[] = "127.0.0.1";
int porta = 8000;

void send_byte(unsigned char byte) {
    if (servidor_conectado) {
        Socket sock(ip, porta);
        sock.write_byte(byte);
    }
}

void print_opcao(int op) {
    if (opcao == op) {
        printw(" >> ");
    } else {
        printw("    ");
    }
}

void print_menu() {
    printw("        * Controle de trens *\n");
    printw("       ***********************\n");

    print_opcao(0);

    if (servidor_conectado) {
        printw("Desconectar do servidor\n");
    } else {
        printw("Conectar ao servidor\n");
    }

    print_opcao(1);
    printw("Desligar todos os trens\n");

    print_opcao(2);
    printw("Ligar todos os trens\n");

    for (int i = 0; i < 4; ++i) {
        print_opcao(3 + i);
        printw("Trem ");
        printw(nomes[i]);

        if (ligado[i]) {
            printw(" (ligado)");
        } else {
            printw(" (desligado)");
        }

        move(5 + i, 31);
        printw("[");

        int j;
        for (j = 0; j < velocidades[i]; ++j) {
            printw("*");
        }

        for (; j < 31; ++j) {
            printw(" ");
        }

        printw("]\n");
    }

    print_opcao(7);
    printw("Sair\n");
}

void do_action() {
    unsigned char byte;
    unsigned char status[4];

    if (opcao == 7) {
        endwin();
        exit(0);
    } else if (opcao == 1 || opcao == 2) {
        ligado[0] = opcao == 2;
        ligado[1] = opcao == 2;
        ligado[2] = opcao == 2;
        ligado[3] = opcao == 2;

        send_byte(opcao == 2);
    } else if (opcao == 0) {
        if (!servidor_conectado) {
            Socket sock(ip, porta);

            sock.write_byte(2);
            status[0] = sock.read_byte();
            status[1] = sock.read_byte();
            status[2] = sock.read_byte();
            status[3] = sock.read_byte();
            sock.close();

            for (int k = 0; k < 4; ++k) {
                velocidades[k] = status[k] & 31;
                ligado[k] = status[k] & 0x20;

                vwprintw("%i ", (int) status[k]);
            }
        }


        servidor_conectado = !servidor_conectado;
    } else {
        ligado[opcao - 3] = !ligado[opcao - 3];

        byte = 8 | (((opcao - 3) & 0x03) << 1) | (ligado[opcao - 3] & 1);
        send_byte(byte);
    }
}

void set_train_speed(int key) {
    int v = velocidades[opcao - 3];
    unsigned char byte;

    if (key == 'a') {
        v = v > 0 ? v - 1 : 0;
        velocidades[opcao - 3] = v > 0 ? v - 1 : 0;
    } else {
        v = v < 31 ? v + 1 : 31;
    }

    velocidades[opcao - 3] = v;

    byte = 128 | (((opcao - 3) & 0x03) << 5) | (v & 31);
    send_byte(byte);
}

int main() {
    int key;
    initscr();
    noecho();
    curs_set(0);

    while (true) {
        clear();
        print_menu();
        refresh();
        key = getch();

        if (key == 's') {
            opcao = opcao < 7 ? opcao + 1 : 7;
        } else if (key == 'w') {
            opcao = opcao > 0 ? opcao - 1 : 0;
        } else if (key == ' ') {
            do_action();
        } else if (key == 'a' || key == 'd') {
            set_train_speed(key);
        }
    }

    endwin();

    return 0;
}
