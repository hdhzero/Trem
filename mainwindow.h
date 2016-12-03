#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "trem.h"
#include <QMainWindow>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateInterface(int,int,int);

private:
    void drawRails();

private:
    Ui::MainWindow *ui;
    Trem* trem1;
    Trem* trem2;
};

#endif // MAINWINDOW_H
