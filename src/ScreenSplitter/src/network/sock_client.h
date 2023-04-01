#pragma once
#include <QObject>
#include <QAbstractSocket>
#include <QTcpServer>

class QFile;
class SockClient : public QObject
{
	Q_OBJECT

public:
    explicit SockClient(QObject* parent = nullptr);

signals:
    void ClientStatus(bool);

public slots:
    void StartTransfer();
    void UpdateProgress(qint64);
    void DisplayError_s(QAbstractSocket::SocketError);
    void SetConnectStat();
    
    void Send();
    void SetMsgFile(QString msg, QString filename);
    void SetAddress(int port, QString add);
    bool SockConnect();
    void DisConn();

public:
    int m_port = -1;
    bool isSending = false;
    bool isConnected = false;
    bool isAddrChanged = false;
    QString m_address;

private:
    QTcpSocket* m_socket_snd_;

    qint64 m_totalBytes_;
    qint64 m_bytesWritten_;
    qint64 m_bytesToWrite_;
    qint64 m_payloadSize_;
    QByteArray m_outBlock_;

    QString m_sndMsg_;
    QString m_snd_filename_;
    QFile* m_sndFile_ = nullptr;
};


