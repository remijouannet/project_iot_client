#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cpu_usage.h"
#include "mem_info.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

    ui->m_CustomPlot->yAxis->setRangeUpper(mem_info::getMemoryTotal()/1024);
    ui->m_CustomPlot->yAxis->setRangeLower(0);


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

    cpu_usage::init();
    cpu_usage::getCurrentValue();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL( timeout() ), this, SLOT( realtimeDataSlot() ) );
    timer->start( 100 );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::realtimeDataSlot()
{

    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.01)
    {
      double value0 = mem_info::getMemoryUsage()/1024;
      double value1 = cpu_usage::getCurrentValue();

      ui->m_CustomPlot->graph(0)->addData(key, value0);
      ui->m_CustomPlot->graph(1)->clearData();
      ui->m_CustomPlot->graph(1)->addData(key, value0);
      ui->m_CustomPlot->graph(0)->removeDataBefore(key-15);

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
