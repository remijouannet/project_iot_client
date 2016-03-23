#ifndef CLIENT_TCP_H
#define CLIENT_TCP_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>

class client_tcp : public QObject
{

Q_OBJECT

public:
    explicit client_tcp(QObject *parent = 0);
    ~client_tcp();
    bool doConnect(QString addr, int port);
    void write(const char* data, int len);
    bool isconnected();
    void ext_disconnected();

public slots:
    void sconnected();
    void sdisconnected();
    void sreadyRead();

private:
    QTcpSocket *socket;
};

#endif // CLIENT_TCP_H
