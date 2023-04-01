#include "sock_svr.h"

#include <QTcpSocket>
#include <QtNetWork>
#include <QTcpServer>

SockSvr::SockSvr()
{
    QObject::connect(&m_tcpServer_, SIGNAL(newConnection()), this, SLOT(AcceptConnection()));
    StartServer();
}

void SockSvr::StartServer()
{
    if (m_tcpServer_.isListening())
    {
        isStart = true;
        return;
    }
    if (!m_tcpServer_.listen(QHostAddress::LocalHost, 5002))
    {
        qDebug() << m_tcpServer_.errorString();
        isStart = false;
        return;
    }
    isStart = true;
    m_totalBytes_recv_ = 0;
    m_bytesReceived_ = 0;
    m_fileNameSize_ = 0;
    m_msgSize_ = 0;
}

void SockSvr::AcceptConnection()
{
    m_socket_recv_ = m_tcpServer_.nextPendingConnection();
    QObject::connect(m_socket_recv_, SIGNAL(readyRead()), this, SLOT(UpdateServerProgress()));
    QObject::connect(m_socket_recv_, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(DisplayError_r(QAbstractSocket::SocketError)));
    QObject::connect(m_socket_recv_, SIGNAL(disconnected()), this, SLOT(ResetServer()));
}

void SockSvr::UpdateServerProgress()
{
    QDataStream in(m_socket_recv_);
    in.setVersion(QDataStream::Qt_5_15);
    if (m_bytesReceived_ <= sizeof(qint64) * 3)
    {
        if ((m_socket_recv_->bytesAvailable() >= sizeof(qint64) * 3) && (m_msgSize_ == 0) && (m_fileNameSize_ == 0))
        {
            in >> m_totalBytes_recv_ >> m_msgSize_ >> m_fileNameSize_;
            m_bytesReceived_ += sizeof(qint64) * 3;
        }
        if (m_socket_recv_->bytesAvailable() >= m_msgSize_ + m_fileNameSize_)
        {
            if (m_msgSize_ != 0)
            {
                in >> m_recvMsg_;
                m_bytesReceived_ += m_msgSize_;
            }
            else
            {
                return;
            }

            if (m_fileNameSize_ != 0)
            {
                in >> m_recv_filename_;
                m_bytesReceived_ += m_fileNameSize_;
                m_recv_file_ = new QFile(QString(m_recv_filename_));
                if (!m_recv_file_->open(QFile::WriteOnly))
                {
                    qDebug() << "server : open file error!";
                    return;
                }
            }
            else
            {
                return;
            }
        }
    }
    if (m_bytesReceived_ < m_totalBytes_recv_)
    {
        m_bytesReceived_ += m_socket_recv_->bytesAvailable();
        m_inBlock = m_socket_recv_->readAll();
        m_recv_file_->write(m_inBlock);
        m_inBlock.resize(0);
    }

    if (m_bytesReceived_ == m_totalBytes_recv_)
    {
        m_totalBytes_recv_ = 0;
        m_bytesReceived_ = 0;
        m_msgSize_ = 0;
        m_fileNameSize_ = 0;
        if (QString(m_recvMsg_) == QString("init"))
        {
            emit ResetDimen();
        }
        //m_socket_recv_->close();
        m_recv_file_->close();
    }
}

void SockSvr::DisplayError_r(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError)
        qDebug() << m_socket_recv_->errorString();
    m_socket_recv_->close();
}

void SockSvr::ResetServer()
{
    m_tcpServer_.close();
    if (!m_tcpServer_.listen(QHostAddress::LocalHost, 5002))
    {
        qDebug() << m_tcpServer_.errorString();
        isStart = false;
        return;
    }
    m_totalBytes_recv_ = 0;
    m_bytesReceived_ = 0;
    m_fileNameSize_ = 0;
}