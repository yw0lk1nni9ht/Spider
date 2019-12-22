TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
	DataFilter/bloomfilter.h \
	DataFilter/murmurhash3.h \
    Request/http_request.h \
    Request/https_request.h \
    Request/request.h \
    Request/requesthandle.h \
	DataFilter/dataclean.h \
    datahandle.h \
    response_parse.h \
    downloadhandle.h \
    threadpool.h \
    StartControl/DefaultSearch.h \
    StartControl/PersonIdSearch.h
SOURCES += \
	DataFilter/bloomfilter.cpp \
	DataFilter/murmurhash3.cpp \
    Request/http_request.cpp \
    Request/https_request.cpp \
	Request/request.cpp \
    Request/requesthandle.cpp \
	DataFilter/dataclean.cpp \
	datahandle.cpp \
        main.cpp \
    response_parse.cpp \
    downloadhandle.cpp \
    StartControl/DefaultSearch.cpp \
    StartControl/PersonIdSearch.cpp

INCLUDEPATH += /usr/local/boost/include
INCLUDEPATH += /usr/local/ssl/openssl/include
INCLUDEPATH += include
INCLUDEPATH += Request
INCLUDEPATH += $$PWD/lib

LIBS += -lpthread
LIBS += -L/usr/local/ssl/openssl/lib -lssl
LIBS += -L/usr/local/ssl/openssl/lib -lcrypto
LIBS += -L/usr/local/boost/lib -lboost_thread
LIBS += -L$$PWD/lib -lmodest
LIBS += -L$$PWD/lib -lcurl

