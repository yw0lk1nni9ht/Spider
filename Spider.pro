TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    Request/http_request.h \
    Request/https_request.h \
    Request/requesthandle.h \
    response_parse.h \
    downloadhandle.h
SOURCES += \
    Request/http_request.cpp \
    Request/https_request.cpp \
    Request/requesthandle.cpp \
        main.cpp \
    response_parse.cpp \
    downloadhandle.cpp

INCLUDEPATH += /usr/local/boost/include
INCLUDEPATH += /usr/local/ssl/openssl/include
INCLUDEPATH += include
INCLUDEPATH += Request
INCLUDEPATH += $$PWD/lib

LIBS += -lpthread
LIBS += -L/usr/local/ssl/openssl/lib -lssl
LIBS += -L/usr/local/ssl/openssl/lib -lcrypto
LIBS += -L$$PWD/lib -lmodest

