QT += core network
CONFIG += c++11

TEMPLATE = app

INCLUDEPATH += $$PWD/../TelegramQt

LIBS += -lssl -lcrypto -lz
LIBS += -L$$OUT_PWD/../TelegramQt
LIBS += -lTelegramQt$${QT_MAJOR_VERSION}

TARGET = testApp

SOURCES = main.cpp \
    TelegramServer.cpp \
    TelegramServerClient.cpp \
    TelegramClientData.cpp

#OTHER_FILES += CMakeLists.txt

HEADERS += \
    TelegramServer.hpp \
    TelegramServerClient.hpp \
    TelegramClientData.hpp
