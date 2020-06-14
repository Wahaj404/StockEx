QT       += core
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# These flags are passed to the C++ linker to link the sqlite3 library. Change the -L path to where you have
# your library installed.
QMAKE_LFLAGS += -LC:\sqlite\ -lsqlite3
INCLUDEPATH += "Frontend\headers"
INCLUDEPATH += "Backend\headers"

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp                        \
    Frontend\\src\\About.cpp        \
    Frontend\\src\\ListingsTab.cpp  \
    Frontend\\src\\MainWindow.cpp   \
    Frontend\\src\\MarketTab.cpp    \
    Frontend\\src\\Portfolio.cpp    \
    Frontend\\src\\Splash.cpp       \
    Frontend\\src\\WatchListTab.cpp \
    Frontend\\src\\OnStack.cpp      \
    Frontend\\src\\LoginWindow.cpp  \
                                    \
    Backend\\src\\Account.cpp       \
    Backend\\src\\Company.cpp       \
    Backend\\src\\Condition.cpp     \
    Backend\\src\\Credential.cpp    \
    Backend\\src\\ID.cpp            \
    Backend\\src\\IRecord.cpp       \
    Backend\\src\\Listing.cpp       \
    Backend\\src\\RealTime.cpp      \
    Backend\\src\\Share.cpp         \
    Backend\\src\\SQLite.cpp        \
    Backend\\src\\SQLiteEx.cpp      \
    Backend\\src\\Transaction.cpp   \
    Backend\\src\\User.cpp          \
    Backend\\src\\WatchList.cpp  

HEADERS += \
    Frontend\\headers\\About.hpp        \
    Frontend\\headers\\ListingsTab.hpp  \
    Frontend\\headers\\MainWindow.hpp   \
    Frontend\\headers\\MarketTab.hpp    \
    Frontend\\headers\\OnStack.hpp      \
    Frontend\\headers\\LoginWindow.hpp  \
    Frontend\\headers\\Portfolio.hpp    \
    Frontend\\headers\\Splash.hpp       \
    Frontend\\headers\\WatchListTab.hpp \
                                        \
    Backend\\headers\\Account.hpp       \
    Backend\\headers\\Company.hpp       \
    Backend\\headers\\Condition.hpp     \
    Backend\\headers\\Credential.hpp    \
    Backend\\headers\\ID.hpp            \
    Backend\\headers\\IRecord.hpp       \ 
    Backend\\headers\\Listing.hpp       \
    Backend\\headers\\RealTime.hpp      \
    Backend\\headers\\Share.hpp         \
    Backend\\headers\\SQLite.hpp        \
    Backend\\headers\\SQLiteEx.hpp      \
    Backend\\headers\\Transaction.hpp   \
    Backend\\headers\\User.hpp          \
    Backend\\headers\\Util.hpp          \
    Backend\\headers\\WatchList.hpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
