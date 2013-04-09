#ifndef SSLSERVER_H
#define SSLSERVER_H

#include <QObject>

#include <QtNetwork>
#include <string>


class Server : public QTcpServer
{
  Q_OBJECT

public:
  virtual void incomingConnection(int socketDescriptor);
};



class sslserver : public QObject
{
    Q_OBJECT
public:
    int ip;
    int port;
    QString key;
    QString certificate;

    explicit sslserver(QObject *parent = 0);
    void listen();

signals:
    void received(const std::string &);

public slots:
    void acceptConnection();
    void handshakeComplete();
    void sslErrors(const QList<QSslError> &errors);
    void receiveMessage();
    void connectionClosed();
    void connectionFailure();

private:
    Server server;
    QList<QSslSocket *> sockets;
    int64_t read_buffer_sz;
};

#endif // SSLSERVER_H
