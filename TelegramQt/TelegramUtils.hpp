#ifndef CTELEGRAMUTILS_HPP
#define CTELEGRAMUTILS_HPP

#include "TelegramNamespace.hpp"
#include "TLValues.hpp"

#include <QStringList>

namespace TelegramUtils
{
    QString maskPhoneNumber(const QString &identifier);
    QStringList maskPhoneNumberList(const QStringList &list);

    QString mimeTypeByStorageFileType(TLValue type);
    TelegramNamespace::MessageType telegramMessageTypeToPublicMessageType(TLValue type);
    TLValue::Value publicMessageTypeToTelegramMessageType(TelegramNamespace::MessageType type);
    TelegramNamespace::MessageAction telegramMessageActionToPublicAction(TLValue action);
    TLValue::Value publicMessageActionToTelegramAction(TelegramNamespace::MessageAction action);

    enum TelegramMessageFlags {
        TelegramMessageFlagNone    = 0,
        TelegramMessageFlagUnread  = 1 << 0,
        TelegramMessageFlagOut     = 1 << 1,
        TelegramMessageFlagForward = 1 << 2,
        TelegramMessageFlagReply   = 1 << 3,
    };

    enum TelegramUserFlag {
        TelegramUserFlagNone = 0,
        TelegramUserFlagAccessHash = 1 << 0, // 1, AccessHash
        TelegramUserFlagFirstName = 1 << 1, // 2, First name
        TelegramUserFlagLastName = 1 << 2, // 4, Last name
        TelegramUserFlagUserName = 1 << 3, // 8, User name
        TelegramUserFlagPhone = 1 << 4, // 16, Phone
        TelegramUserFlagHasPhoto = 1 << 5, // 32, Photo
        TelegramUserFlagStatus = 1 << 6, // 64, Status
        TelegramUserFlagSelf = 1 << 10, // 1024
        TelegramUserFlagIsContact = 1 << 11, // 2048
        TelegramUserFlagIsMutualContact = 1 << 12, // 4096
        TelegramUserFlagDeleted = 1 << 13, // 8192
        TelegramUserFlagBot = 1 << 14, // 16384, Bot with version
        TelegramUserFlagBotChatHistory = 1 << 15, // 32768
        TelegramUserFlagBotNoChats = 1 << 16, // 65536
        TelegramUserFlagVerified = 1 << 17, // 131072
        TelegramUserFlagRestricted = 1 << 18, // 262144, Restricted with a reason
        TelegramUserFlagBotInlinePlaceholder = 1 << 19, // 524288, Bot with placeholder
        TelegramUserFlagMin = 1 << 20, // 1048576
        TelegramUserFlagBotInlineGeo = 1 << 21, // 2097152
    };
}

#endif // CTELEGRAMUTILS_HPP
