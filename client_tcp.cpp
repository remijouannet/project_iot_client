#include <stdlib.h>

#include "client_tcp.h"
#include "mainwindow.h"

client_tcp::client_tcp(QObject *parent) :
    QObject(parent)
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()),this, SLOT(sconnected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(sdisconnected()));
    connect(socket, SIGNAL(readyRead()),this, SLOT(sreadyRead()));
}

client_tcp::~client_tcp()
{
    socket->close();
}

bool client_tcp::doConnect(QString addr, int port)
{
    qDebug() << "connecting...";
    ext_disconnected();
    socket->connectToHost(addr, port, QIODevice::ReadWrite);
    return socket->waitForConnected();
}

void client_tcp::sconnected()
{
    qDebug() << "connected...";
}

void client_tcp::sdisconnected()
{
    qDebug() << "disconnected...";
}

void client_tcp::sreadyRead()
{
    QByteArray result = socket->readAll();

    if(memcmp(result, "1", 1) == 0){
        result.remove(0, 2);
        MainWindow::value0 = strtod(result.data(), NULL);
    }else if(memcmp(result, "2", 1) == 0){
        result.remove(0, 2);
        MainWindow::value1 = strtod(result.data(), NULL);
    }else if(memcmp(result, "3", 1) == 0){
        result.remove(0, 2);
        MainWindow::value2 = strtod(result.data(), NULL);
    }
}

void client_tcp::write(const char* data, int len)
{
    socket->flush();
    socket->write(data, len);
}

bool client_tcp::isconnected()
{
    if(socket->state() == QAbstractSocket::ConnectedState){
        return true;
    }else{
        return false;
    }
}

void client_tcp::ext_disconnected()
{
    socket->close();
}
