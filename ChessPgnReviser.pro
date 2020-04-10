QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

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
    gui/adapters/thcposition.cpp \
    gui/chessboard/chessboard.cpp \
    gui/mainwindow.cpp \
    libs/thc-chess-library/ChessPosition.cpp \
    libs/thc-chess-library/ChessRules.cpp \
    libs/thc-chess-library/Move.cpp \
    libs/thc-chess-library/Portability.cpp \
    libs/thc-chess-library/PrivateChessDefs.cpp \
    main.cpp \

HEADERS += \
    gui/adapters/thcposition.h \
    gui/chessboard/IPosition.h \
    gui/chessboard/chessboard.h \
    gui/mainwindow.h \
    libs/thc-chess-library/ChessDefs.h \
    libs/thc-chess-library/ChessPosition.h \
    libs/thc-chess-library/ChessPositionRaw.h \
    libs/thc-chess-library/ChessRules.h \
    libs/thc-chess-library/DebugPrintf.h \
    libs/thc-chess-library/GeneratedLookupTables.h \
    libs/thc-chess-library/HashLookup.h \
    libs/thc-chess-library/Move.h \
    libs/thc-chess-library/Portability.h \
    libs/thc-chess-library/PrivateChessDefs.h \
    libs/thc-chess-library/thc-original-umbrella.h \

TRANSLATIONS += \
    ChessPgnReviser_en_GB.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \
    LICENSE.md \
    README.md \
    resources/chess_vectors/Chess_bdt45.svg \
    resources/chess_vectors/Chess_blt45.svg \
    resources/chess_vectors/Chess_kdt45.svg \
    resources/chess_vectors/Chess_klt45.svg \
    resources/chess_vectors/Chess_ndt45.svg \
    resources/chess_vectors/Chess_nlt45.svg \
    resources/chess_vectors/Chess_pdt45.svg \
    resources/chess_vectors/Chess_plt45.svg \
    resources/chess_vectors/Chess_qdt45.svg \
    resources/chess_vectors/Chess_qlt45.svg \
    resources/chess_vectors/Chess_rdt45.svg \
    resources/chess_vectors/Chess_rlt45.svg \
    resources/icons/swap.svg

RESOURCES += \
    resources.qrc \
    resources.qrc
