TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    http_request.cpp \
    https_request.cpp \
    response_parse.cpp \
    downloadhandle.cpp


#DEFINES +=BOOST_USE_LIB

##关闭BOOST的自动连库
#DEFINES += BOOST_ALL_NO_LIB=1
##BOOST使用动态库
#DEFINES += BOOST_ALL_DYN_LINK=1

INCLUDEPATH += /usr/local/boost/include
INCLUDEPATH += /usr/local/ssl/openssl/include
INCLUDEPATH += include
INCLUDEPATH += $$PWD/lib
#LIBS += -L/usr/local/boost/lib -lboost_wave
#LIBS += -L/usr/local/boost/lib -lboost_log
#LIBS += -L/usr/local/boost/lib -lboost_graph
#LIBS += -L/usr/local/boost/lib -lboost_regex
#LIBS += -L/usr/local/boost/lib -lboost_timer
#LIBS += -L/usr/local/boost/lib -lboost_atomic
#LIBS += -lboost_chrono
#LIBS += -L/usr/local/boost/lib -lboost_locale
#LIBS += -L/usr/local/boost/lib -lboost_random
#LIBS += -L/usr/local/boost/lib -lboost_system
#LIBS += -L/usr/local/boost/lib -lboost_thread
#LIBS += -L/usr/local/boost/lib -lboost_context
#LIBS += -L/usr/local/boost/lib -lboost_contract
#LIBS += -L/usr/local/boost/lib -lboost_math_c99
#LIBS += -L/usr/local/boost/lib -lboost_math_tr1
#LIBS += -L/usr/local/boost/lib -lboost_python27
#LIBS += -L/usr/local/boost/lib -lboost_container
#LIBS += -L/usr/local/boost/lib -lboost_coroutine
#LIBS += -L/usr/local/boost/lib -lboost_date_time
#LIBS += -L/usr/local/boost/lib -lboost_exception
#LIBS += -L/usr/local/boost/lib -lboost_iostreams
#LIBS += -L/usr/local/boost/lib -lboost_log_setup
#LIBS += -L/usr/local/boost/lib -lboost_math_c99f
#LIBS += -L/usr/local/boost/lib -lboost_math_c99l
#LIBS += -L/usr/local/boost/lib -lboost_filesystem
#LIBS += -L/usr/local/boost/lib -lboost_type_erasure
#LIBS += -L/usr/local/boost/lib -lboost_serialization
#LIBS += -L/usr/local/boost/lib -lboost_wserialization
#LIBS += -L/usr/local/boost/lib -lboost_program_options
#LIBS += -lpthread


#LIBS += /home/yw0lk1nni9ht/projects/FrameworkCompilation/boost_1_70_0/stage/lib/libboost_thread.a
#LIBS += /home/yw0lk1nni9ht/projects/FrameworkCompilation/boost_1_70_0/stage/lib/libboost_system.a
#LIBS += /home/yw0lk1nni9ht/projects/FrameworkCompilation/boost_1_70_0/stage/lib/libboost_chrono.a
#LIBS += /home/yw0lk1nni9ht/projects/FrameworkCompilation/boost_1_70_0/stage/lib/libboost_log.a
#LIBS += /home/yw0lk1nni9ht/projects/FrameworkCompilation/boost_1_70_0/stage/lib/libboost_atomic.a
#LIBS += /home/yw0lk1nni9ht/projects/FrameworkCompilation/boost_1_70_0/stage/lib/libboost_iostreams.a
#LIBS += /home/yw0lk1nni9ht/projects/FrameworkCompilation/boost_1_70_0/stage/lib/libboost_wave.a
#LIBS += /home/yw0lk1nni9ht/projects/FrameworkCompilation/boost_1_70_0/stage/lib/libboost_graph.a
#LIBS += /home/yw0lk1nni9ht/projects/FrameworkCompilation/boost_1_70_0/stage/lib/libboost_regex.a
#LIBS += /home/yw0lk1nni9ht/projects/FrameworkCompilation/boost_1_70_0/stage/lib/libboost_timer.a
#LIBS += /home/yw0lk1nni9ht/projects/FrameworkCompilation/boost_1_70_0/stage/lib/libboost_locale.a
#LIBS += /home/yw0lk1nni9ht/projects/FrameworkCompilation/boost_1_70_0/stage/lib/libboost_random.a
#LIBS += /home/yw0lk1nni9ht/projects/FrameworkCompilation/boost_1_70_0/stage/lib/libboost_context.a
#LIBS += /home/yw0lk1nni9ht/projects/FrameworkCompilation/boost_1_70_0/stage/lib/libboost_contract.a
#LIBS += /home/yw0lk1nni9ht/projects/FrameworkCompilation/boost_1_70_0/stage/lib/libboost_container.a
#LIBS += /home/yw0lk1nni9ht/projects/FrameworkCompilation/boost_1_70_0/stage/lib/libboost_coroutine.a
#LIBS += /home/yw0lk1nni9ht/projects/FrameworkCompilation/boost_1_70_0/stage/lib/libboost_date_time.a
#LIBS += /home/yw0lk1nni9ht/projects/FrameworkCompilation/boost_1_70_0/stage/lib/libboost_exception.a
#LIBS += /home/yw0lk1nni9ht/projects/FrameworkCompilation/boost_1_70_0/stage/lib/libboost_filesystem.a
LIBS += -lpthread
LIBS += -L/usr/local/ssl/openssl/lib -lssl
LIBS += -L/usr/local/ssl/openssl/lib -lcrypto
LIBS += -L$$PWD/lib -lmodest
HEADERS += \
    http_request.h \
    https_request.h \
    response_parse.h \
    downloadhandle.h
