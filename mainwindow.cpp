#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    trem1 = new Trem(1,144,130);
    trem2 = new Trem(2,144,230);

    connect(trem1,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem2,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));

    trem1->start();
    trem2->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawRails() {

}

void MainWindow::updateInterface(int id, int x, int y)
{
    switch(id){
        case 1:
            ui->labelTrem01->setGeometry(x,y,15,15);
            break;

        case 2:
            ui->labelTrem02->setGeometry(x,y,15,15);
            break;

        default:
            break;
    }
}

