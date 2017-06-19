#ifndef TELEGRAMSERVER_HPP
#define TELEGRAMSERVER_HPP

#include <QObject>
#include "../TelegramQt/TLTypes.hpp"

QT_BEGIN_NAMESPACE
class QTcpServer;
class QTcpSocket;
class QTimer;
QT_END_NAMESPACE

class TelegramServer : public QObject
{
    Q_OBJECT
public:
    explicit TelegramServer(QObject *parent = nullptr);

    void setDcOption(const TLDcOption &option);

    void start();

signals:

public slots:

protected slots:
    void onNewConnection();

private:
    QTcpServer *m_serverSocket;
    TLDcOption m_dcOption;
};

#endif // TELEGRAMSERVER_HPP
