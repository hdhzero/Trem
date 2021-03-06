#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "trem.h"
#include "servidor.h"
#include <QMainWindow>
#include <QMutex>

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
    void closeEvent(QCloseEvent*);

public slots:
    void updateInterface(int,int,int);

private:
    Ui::MainWindow *ui;
    Trem* trem1;
    Trem* trem2;
    Trem* trem3;
    Trem* trem4;
    Servidor servidor;
    QMutex trilhos[23]; // os 10 sao hack
                           // para evitar criar muxes e repassar eles para outras classes
                           // trilhos ja esta disponivel para outras classes. Basta usar os indices
                           // Ou seja, a partir do trilho 14 nao sao trilhos de fato.
};

#endif // MAINWINDOW_H
