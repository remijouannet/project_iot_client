#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "client_tcp.h"
#include "protocole.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static double value0, value1, value2;

private slots:
    void realtimeDataSlot();
    void button_connect();
    void button_disconnect();

private:
    Ui::MainWindow *ui;
    QCPItemText *m_ValueIndex;

    qreal timeInterval;

    QVector<qreal> m_YData;
    QVector<qreal> m_XData;

    void plot1();
    void plot2();

    client_tcp s;
};

#endif // MAINWINDOW_H
