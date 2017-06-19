#include "TelegramServerClient.hpp"
#include "TelegramClientData.hpp"

#include "../TelegramQt/TLTypes.hpp"
#include "../TelegramQt/CTelegramStream.hpp"

TelegramServerClient::TelegramServerClient(QObject *parent) :
    QObject(parent)
{

}

bool TelegramServerClient::isOnline()
{

}

void TelegramServerClient::setSocket(QTcpSocket *socket)
{
}

void TelegramServerClient::onUpdatesGetState()
{
    CTelegramStream output;
    TLUpdatesState result;
//    result.pts = m_data->updateState().pts();
    output << result;
}
