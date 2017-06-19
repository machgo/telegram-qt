#include "TelegramServer.hpp"

#include <QLoggingCategory>
#include <QTcpServer>

Q_LOGGING_CATEGORY(loggingCategoryServer, "telegram.server.main", QtWarningMsg)

TelegramServer::TelegramServer(QObject *parent) :
    QObject(parent)
{
    m_serverSocket = new QTcpServer(this);
    connect(m_serverSocket, &QTcpServer::newConnection, this, &TelegramServer::onNewConnection);
}

void TelegramServer::setDcOption(const TLDcOption &option)
{
    m_dcOption = option;
}

void TelegramServer::start()
{
    m_serverSocket->listen(QHostAddress::Any, m_dcOption.port);
}

void TelegramServer::onNewConnection()
{
    QTcpSocket *newConnection = m_serverSocket->nextPendingConnection();
    if (newConnection == nullptr) {
        qCDebug(loggingCategoryServer) << "no expected pending connection";
        return;
    }
}
