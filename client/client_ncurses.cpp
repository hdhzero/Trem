#include "Socket.h"
#include <ncurses.h>

bool servidor_conectado = false;
int ligado[4] = {0, 0, 1, 0};
int velocidades[4] = {17, 0, 0, 0};
int opcao = 0;
char* nomes[] = {"amarelo", "vermelho", "azul", "preto"};

void print_menu() {
    printw("        * Controle de trens *\n");
    printw("       ***********************\n");

    if (opcao == 0) {
        printw("[*] ");
    } else {
        printw("[ ] ");
    }

    if (servidor_conectado) {
        printw("Desconectar do servidor\n");
    } else {
        printw("Conectar ao servidor\n");
    }

    if (opcao == 1) {
        printw("[*] ");
    } else {
        printw("[ ] ");
    }

    printw("Desligar todos os trens\n");

    if (opcao == 2) {
        printw("[*] ");
    } else {
        printw("[ ] ");
    }

    printw("Ligar todos os trens\n");

    for (int i = 0; i < 4; ++i) {
        if (opcao == 3 + i) {
            printw("[*] ");
        } else {
            printw("[ ] ");
        }

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

        for (; j < 32; ++j) {
            printw(" ");
        }

        printw("]\n");
    }

    if (opcao == 7) {
        printw("[*] ");
    } else {
        printw("[ ] ");
    }

    printw("Sair\n");
}


int main() {
    int key;
    initscr();

    while (true) {
        clear();
        print_menu();
        refresh();
        key = getch();

        if (key == 's') {
            ++opcao;
        } else if (key == 'w') {
            --opcao;
        }
    }

    endwin();

    return 0;
}
