#include <stdlib.h>

#include "client_tcp.h"
#include "mainwindow.h"
#include "protocole.h"

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

    protocole::reponse reponse;

    protocole::parse_reponse((char*)result.constData(), &reponse);

    if(reponse.query == 1){
        MainWindow::value0 = strtod(reponse.message, NULL);
    }else if(reponse.query == 2){
        MainWindow::value1 = strtod(reponse.message, NULL);
    }else if(reponse.query == 3){
        MainWindow::value2 = strtod(reponse.message, NULL);
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
