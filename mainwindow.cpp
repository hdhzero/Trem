#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    servidor(8000)
{
    ui->setupUi(this);

    trem1 = new Trem(1, 144, 130, trilhos);
    trem2 = new Trem(2, 144, 230, trilhos);
    trem3 = new Trem(3, 341, 230, trilhos);
    trem4 = new Trem(4, 295, 390, trilhos);

    servidor.addTrem(trem1, 1);
    servidor.addTrem(trem2, 2);
    servidor.addTrem(trem3, 3);
    servidor.addTrem(trem4, 4);

    connect(trem1,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem2,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem3,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem4,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));

    trem1->start();
    trem2->start();
    trem3->start();
    trem4->start();
    servidor.start();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateInterface(int id, int x, int y) {
    switch(id){
        case 1:
            ui->labelTrem01->setGeometry(x,y,15,15);
            break;

        case 2:
            ui->labelTrem02->setGeometry(x,y,15,15);
            break;

        case 3:
            ui->labelTrem03->setGeometry(x,y,15,15);
            break;

        case 4:
            ui->labelTrem04->setGeometry(x,y,15,15);
            break;

        default:
            break;
    }
}

