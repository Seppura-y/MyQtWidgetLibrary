#include "sock_client.h"
#include <QtNetwork>
#include <QThread>

SockClient::SockClient(QObject* parent) : QObject(parent)
{
    m_address = QString("127.0.0.1");
    m_port = 5001;
    m_totalBytes_ = 0;
    m_bytesWritten_ = 0;
    m_bytesToWrite_ = 0;
    m_payloadSize_ = 64 * 1024;

    m_socket_snd_ = new QTcpSocket(this);
    //QObject::connect(m_socket_snd_, SIGNAL(connected()), this, SLOT(SetConnectStat()));
    QObject::connect(m_socket_snd_, SIGNAL(disconnected()), this, SLOT(SetConnectStat()));
    QObject::connect(m_socket_snd_, SIGNAL(bytesWritten(qint64)), this, SLOT(UpdateProgress(qint64)));
    QObject::connect(m_socket_snd_, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(DisplayError_s(QAbstractSocket::SocketError)));

    //SockConnect();
}

void SockClient::SetMsgFile(QString msg, QString filename)
{
    m_sndMsg_ = msg;
    m_snd_filename_ = filename;
}

void SockClient::Send()
{
    if (isConnected)
    {
        StartTransfer();
    }
}


void SockClient::StartTransfer() 
{

    m_sndFile_ = new QFile(m_snd_filename_);
    if (!m_sndFile_->open(QFile::ReadOnly)) 
    {
        qDebug() << "client£ºopen file error!";
        return;
    }
    m_totalBytes_ = m_sndFile_->size();
    QDataStream sendOut(&m_outBlock_, QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_5_15);
    QString currentFileName = m_snd_filename_.right(m_snd_filename_.size() - m_snd_filename_.lastIndexOf('/') - 1);

    QByteArray arr_filename;
    QByteArray arr_msg;

    arr_msg.append(m_sndMsg_);
    arr_filename.append(currentFileName);

    qint64 block_size = 0;
    qint64 msg_size = 0;
    qint64 filename_size = 0;
    sendOut << qint64(0) << qint64(0) << qint64(0);
    block_size = m_outBlock_.size();

    sendOut << arr_msg;
    msg_size = m_outBlock_.size() - block_size;
    block_size = m_outBlock_.size();

    sendOut << arr_filename;
    filename_size = m_outBlock_.size() - block_size;
    block_size = m_outBlock_.size();

    m_totalBytes_ += block_size;

    sendOut.device()->seek(0);
    sendOut << m_totalBytes_ << msg_size << filename_size;

    m_bytesToWrite_ = m_totalBytes_ - m_socket_snd_->write(m_outBlock_);
    m_outBlock_.resize(0);
}

void SockClient::UpdateProgress(qint64 numBytes)
{
    m_bytesWritten_ += (int)numBytes;
    if (m_bytesToWrite_ > 0)
    {
        m_outBlock_ = m_sndFile_->read(qMin(m_bytesToWrite_, m_payloadSize_));
        m_bytesToWrite_ -= (int)m_socket_snd_->write(m_outBlock_);
        m_outBlock_.resize(0);
    }
    else
    {
        m_sndFile_->close();
    }

    if (m_bytesWritten_ == m_totalBytes_)
    {
        //isSending = false;
        m_sndFile_->close();
        //m_socket_snd_->close();
    }
}

void SockClient::DisplayError_s(QAbstractSocket::SocketError)
{
    qDebug() << m_socket_snd_->errorString();
    m_socket_snd_->close();
    //isSending = false;
}


void SockClient::SetConnectStat()
{
    qDebug() << "disconnect";
    isConnected = false;
    emit ClientStatus(isConnected);
}

bool SockClient::SockConnect()
{
    qDebug() << "socket connect current thread id : " << QThread::currentThreadId();
    m_socket_snd_->setSocketOption(QAbstractSocket::KeepAliveOption, true);
    m_socket_snd_->connectToHost(m_address, m_port);
    isAddrChanged = false;
    while (!m_socket_snd_->waitForConnected() && !isAddrChanged)
    {
        qDebug() << "connect failed : " << m_socket_snd_->errorString();
        m_socket_snd_->connectToHost(m_address, m_port);
    }
    if (isAddrChanged)
    {
        return false;
    }

    isConnected = true;
    emit ClientStatus(isConnected);
    qDebug() << "connect success";
    return true;
}

void SockClient::SetAddress(int port, QString add)
{
    m_port = port;
    m_address = add;
    isAddrChanged = true;
    if (isConnected)
    {
        m_socket_snd_->close();
        //isConnected = false;
    }

}

void SockClient::DisConn()
{
    if (isConnected)
        m_socket_snd_->close();

    //isConnected = false;
}