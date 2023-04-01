#pragma once
#include <qobject.h>
#include <QAbstractSocket>
#include <QTcpServer>
class QFile;
class QTcpSocket;

class SockSvr : public QObject
{
	Q_OBJECT

public:
    SockSvr();

signals:
    void ResetDimen();

public slots:
    void StartServer();
    void AcceptConnection();
    void UpdateServerProgress();
    void DisplayError_r(QAbstractSocket::SocketError socketError);
    void ResetServer();

public:
    bool isStart = false;

private:
    QTcpServer m_tcpServer_;
    QTcpSocket* m_socket_recv_;

    qint64 m_totalBytes_recv_;
    qint64 m_msgSize_;
    qint64 m_fileNameSize_;
    qint64 m_bytesReceived_;
    QByteArray m_recvMsg_;
    QByteArray m_recv_filename_;
    QFile* m_recv_file_;
    QByteArray m_inBlock;

};

