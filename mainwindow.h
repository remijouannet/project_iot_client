#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void realtimeDataSlot();

private:
    Ui::MainWindow *ui;
    QCPItemText *m_ValueIndex;

    qreal timeInterval;

    QVector<qreal> m_YData;
    QVector<qreal> m_XData;
};

#endif // MAINWINDOW_H
