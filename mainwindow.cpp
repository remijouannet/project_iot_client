#include <QHostAddress>

#include "mainwindow.h"
#include "ui_mainwindow.h"

double MainWindow::value0 = 0;
double MainWindow::value1 = 0;
double MainWindow::value2 = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    plot1();
    plot2();

    connect(ui->pushButton, SIGNAL( released() ), this, SLOT( button_connect() ) );

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL( timeout() ), this, SLOT( realtimeDataSlot() ) );
    timer->start( 80 );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::button_connect()
{


    s.doConnect(ui->lineEdit_2->text(), ui->lineEdit->text().toInt());

    char buffer[500] = {0};
    int len = 0;
    protocole::send_query(&buffer[0], (char*)ui->lineEdit_3->text().toStdString().c_str(), 3, &len);
    s.write(&buffer[0], len);
}

void MainWindow::button_disconnect()
{
    s.ext_disconnected();
}

void MainWindow::plot1()
{
    ui->m_CustomPlot->addGraph();
    ui->m_CustomPlot->graph(0)->setPen(QPen(Qt::red));
    ui->m_CustomPlot->graph(0)->setBrush(QBrush(Qt::red));
    ui->m_CustomPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->m_CustomPlot->graph(0)->setAntialiasedFill(true);

    ui->m_CustomPlot->addGraph();
    ui->m_CustomPlot->graph(1)->setPen(QPen(Qt::red));
    ui->m_CustomPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->m_CustomPlot->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);

    ui->m_CustomPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->m_CustomPlot->xAxis->setDateTimeFormat("");
    ui->m_CustomPlot->xAxis->setAutoTickStep(true);
    ui->m_CustomPlot->axisRect()->setupFullAxesBox();

    ui->m_CustomPlot->yAxis->setRangeLower(0);
}

void MainWindow::plot2()
{
    ui->m_CustomPlot2->addGraph();
    ui->m_CustomPlot2->graph(0)->setPen(QPen(Qt::blue));
    ui->m_CustomPlot2->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
    ui->m_CustomPlot2->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->m_CustomPlot2->graph(0)->setAntialiasedFill(true);

    ui->m_CustomPlot2->addGraph();
    ui->m_CustomPlot2->graph(1)->setPen(QPen(Qt::blue));
    ui->m_CustomPlot2->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->m_CustomPlot2->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);

    ui->m_CustomPlot2->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->m_CustomPlot2->xAxis->setDateTimeFormat("");
    ui->m_CustomPlot2->xAxis->setAutoTickStep(true);
    ui->m_CustomPlot2->axisRect()->setupFullAxesBox();

    ui->m_CustomPlot2->yAxis->setRangeUpper(100);
    ui->m_CustomPlot2->yAxis->setRangeLower(0);
}

void MainWindow::realtimeDataSlot()
{
    if(s.isconnected()){
        char buffer[500] = {0};
        int len = 0;

        protocole::send_query(&buffer[0], (char*)ui->lineEdit_3->text().toStdString().c_str(), 1, &len);
        s.write(&buffer[0], len);
        protocole::send_query(&buffer[0], (char*)ui->lineEdit_3->text().toStdString().c_str(), 2, &len);
        s.write(&buffer[0], len);

        double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
        static double lastPointKey = 0;
        if (key-lastPointKey > 0.01)
        {
          double value0 = MainWindow::value0/1024;
          double value1 = MainWindow::value1;
          double value2 = MainWindow::value2/1024;

          ui->m_CustomPlot->graph(0)->addData(key, value0);
          ui->m_CustomPlot->graph(1)->clearData();
          ui->m_CustomPlot->graph(1)->addData(key, value0);
          ui->m_CustomPlot->graph(0)->removeDataBefore(key-15);
          ui->m_CustomPlot->yAxis->setRangeUpper(value2);

          ui->m_CustomPlot2->graph(0)->addData(key, value1);
          ui->m_CustomPlot2->graph(1)->clearData();
          ui->m_CustomPlot2->graph(1)->addData(key, value1);
          ui->m_CustomPlot2->graph(0)->removeDataBefore(key-15);

          lastPointKey = key;
        }

        ui->m_CustomPlot->xAxis->setRange(key+0.25, 15, Qt::AlignRight);
        ui->m_CustomPlot->replot();

        ui->m_CustomPlot2->xAxis->setRange(key+0.25, 15, Qt::AlignRight);
        ui->m_CustomPlot2->replot();
    }
}
