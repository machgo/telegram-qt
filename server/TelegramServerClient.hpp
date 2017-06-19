#ifndef TELEGRAMSERVERCLIENT_HPP
#define TELEGRAMSERVERCLIENT_HPP

#include <QObject>

QT_FORWARD_DECLARE_CLASS(QTcpSocket)

class TelegramClientData;

class TelegramServerClient : public QObject
{
    Q_OBJECT
public:
    explicit TelegramServerClient(QObject *parent = nullptr);

    bool isOnline();

    void setSocket(QTcpSocket *socket);

signals:
    void becomeOnline();

public slots:

protected slots:
    void onUpdatesGetState();

private:
    TelegramClientData *m_data;
    QTcpSocket *m_socket;

};

#endif // TELEGRAMSERVERCLIENT_HPP
