QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    artistwindow.cpp \
    homewindow.cpp \
    mainapp.cpp \
    mainwindow.cpp \
    museumwindow.cpp \
    stylewindow.cpp \
    workswindow.cpp

HEADERS += \
    artistwindow.h \
    homewindow.h \
    mainwindow.h \
    museumwindow.h \
    stylewindow.h \
    workswindow.h

FORMS += \
    artistwindow.ui \
    homewindow.ui \
    mainwindow.ui \
    museumwindow.ui \
    stylewindow.ui \
    workswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# MySQL/C++ Connector 2


# MySQL/C++ Connector
INCLUDEPATH += C:/mysql_conn/mysql-connector-c++-9.3.0-winx64/include
INCLUDEPATH += C:/mysql_conn/mysql-connector-c++-9.3.0-winx64/include/jdbc

LIBS += -LC:/mysql_conn/mysql-connector-c++-9.3.0-winx64/lib64/vs14 -lmysqlcppconn
QMAKE_LFLAGS += -L"C:/mysql_conn/mysql-connector-c++-9.3.0-winx64/lib64"
