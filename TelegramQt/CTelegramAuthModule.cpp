#include "CTelegramAuthModule.hpp"

#include "CTelegramConnection.hpp"
#include "TelegramNamespace_p.hpp"
#include "Utils.hpp"

#include <QDebug>

#ifdef DEVELOPER_BUILD
#include "TLTypesDebug.hpp"
#endif

CTelegramAuthModule::CTelegramAuthModule(QObject *parent) :
    CTelegramModule(parent)
{
}

void CTelegramAuthModule::onConnectionStatusChanged()
{
    m_passwordInfo.clear();
}

void CTelegramAuthModule::clear()
{
    m_passwordInfo.clear();
}

bool CTelegramAuthModule::logOut()
{
    if (!activeConnection()) {
        return false;
    }

    activeConnection()->authLogOut();
    return true;
}

void CTelegramAuthModule::requestPhoneStatus(const QString &phoneNumber)
{
    if (!activeConnection()) {
        return;
    }
    activeConnection()->authCheckPhone(phoneNumber);
}

quint64 CTelegramAuthModule::getPassword()
{
    if (!activeConnection()) {
        return 0;
    }

    m_passwordInfo.clear();

    return activeConnection()->accountGetPassword();
}

void CTelegramAuthModule::tryPassword(const QByteArray &salt, const QByteArray &password)
{
    if (!activeConnection()) {
        return;
    }

    const QByteArray pwdData = salt + password + salt;
    const QByteArray pwdHash = Utils::sha256(pwdData);

    activeConnection()->authCheckPassword(pwdHash);
}

void CTelegramAuthModule::tryPassword(const QString &password)
{
    if (m_passwordInfo.isEmpty()) {
        qWarning() << Q_FUNC_INFO << "There is no known salts to try password. Get it by getPassword() call.";
    }
    tryPassword(m_passwordInfo.first().currentSalt, password.toUtf8());
}

void CTelegramAuthModule::signIn(const QString &phoneNumber, const QString &authCode)
{
    if (!activeConnection()) {
        return;
    }
    activeConnection()->signIn(phoneNumber, authCode);
}

void CTelegramAuthModule::signUp(const QString &phoneNumber, const QString &authCode, const QString &firstName, const QString &lastName)
{
    if (!activeConnection()) {
        return;
    }
    activeConnection()->signUp(phoneNumber, authCode, firstName, lastName);
}

void CTelegramAuthModule::requestPhoneCode(const QString &phoneNumber)
{
    if (!activeConnection()) {
        qWarning() << Q_FUNC_INFO << "Can't request phone code: there is no active connection.";
        return;
    }

//    if (m_dcConfiguration.isEmpty()) {
//        qWarning() << Q_FUNC_INFO << "Can't request phone code: DC Configuration is unknown.";
//        return;
//    }

    m_requestedCodeForPhone = phoneNumber;
    activeConnection()->requestPhoneCode(phoneNumber);
}

void CTelegramAuthModule::onUnauthorizedErrorReceived(TelegramNamespace::UnauthorizedError errorCode)
{
    switch (errorCode) {
    case TelegramNamespace::UnauthorizedSessionPasswordNeeded:
        activeConnection()->accountGetPassword();
        break;
    default:
        break;
    }
}

void CTelegramAuthModule::onPasswordReceived(const TLAccountPassword &password, quint64 requestId)
{
#ifdef DEVELOPER_BUILD
    qDebug() << Q_FUNC_INFO << password << requestId;
#else
    qDebug() << Q_FUNC_INFO << requestId;
#endif

    m_passwordInfo.insert(requestId, password);
    emit passwordInfoReceived(requestId);
}

void CTelegramAuthModule::onWantedMainDcChanged(quint32 dc, const QString &dcForPhoneNumber)
{
    qDebug() << Q_FUNC_INFO << dc << "for phone number" << Telegram::Utils::maskPhoneNumber(dcForPhoneNumber);
    setWantedDc(dc);
}

void CTelegramAuthModule::onNewConnection(CTelegramConnection *connection)
{
    connect(connection, &CTelegramConnection::passwordReceived, this, &CTelegramAuthModule::onPasswordReceived);
    connect(connection, &CTelegramConnection::phoneCodeRequired, this, &CTelegramAuthModule::phoneCodeRequired);
    connect(connection, &CTelegramConnection::authSignErrorReceived, this, &CTelegramAuthModule::authSignErrorReceived);
    connect(connection, &CTelegramConnection::authorizationErrorReceived, this, &CTelegramAuthModule::authorizationErrorReceived);
    connect(connection, &CTelegramConnection::phoneStatusReceived, this, &CTelegramAuthModule::phoneStatusReceived);
    connect(connection, &CTelegramConnection::wantedMainDcChanged, this, &CTelegramAuthModule::onWantedMainDcChanged);

    // Should be done only for the main connection, but probably it is safe to connect to all connections for now
    connect(connection, &CTelegramConnection::loggedOut, this, &CTelegramAuthModule::loggedOut);
}

bool CTelegramAuthModule::getPasswordData(Telegram::PasswordInfo *passwordInfo, quint64 requestId) const
{
    qDebug() << Q_FUNC_INFO << requestId;
    if (m_passwordInfo.isEmpty()) {
        qWarning() << Q_FUNC_INFO << "No password data";
        return false;
    }
    if (requestId == 0) {
        requestId = m_passwordInfo.keys().first();
        qDebug() << Q_FUNC_INFO << "Zero call mapped to " << requestId;
    }
    if (!m_passwordInfo.contains(requestId)) {
        qWarning() << Q_FUNC_INFO << "Password data not found for id" << requestId;
        return false;
    }

    TLAccountPassword &data = *passwordInfo->d;
    data = m_passwordInfo.value(requestId);
    return true;
}
