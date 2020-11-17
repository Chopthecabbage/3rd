#include "mytcpsocket.h"

MyTcpSocket::MyTcpSocket(QObject *parent) :
    QObject(parent)
{
}


void MyTcpSocket::doConnect()
{
    socket = new QTcpSocket(this);
    socket->connectToHost(QHostAddress("10.10.20.240"),8001);
    if(socket->waitForConnected(3000))
    {
        qDebug() << "Connected!";

        // send
        socket->write("Hello server\r\n\r\n");
        socket->waitForBytesWritten(1000);
        socket->waitForReadyRead(3000);
        qDebug() << "Reading :" << socket->bytesAvailable();

        // get the data
        qDebug() << socket->readAll();

        // close the connection
        socket->close();
    }
    else
    {
        qDebug() << "Not connected!";
    }
}
