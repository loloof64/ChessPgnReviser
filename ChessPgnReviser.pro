QT       += core gui

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
    gui/chessboard.cpp \
    libagchess/Bitboard.cpp \
    libagchess/Bitboard_MoveGen.cpp \
    libagchess/Board.cpp \
    libagchess/Board_MoveGen.cpp \
    libagchess/Color.cpp \
    libagchess/ColoredPiece.cpp \
    libagchess/DatabaseFilter.cpp \
    libagchess/EditablePosition.cpp \
    libagchess/FEN.cpp \
    libagchess/GameHeaders.cpp \
    libagchess/GameTree.cpp \
    libagchess/Move.cpp \
    libagchess/PGNDatabase.cpp \
    libagchess/PGNLexer.cpp \
    libagchess/Piece.cpp \
    libagchess/Position.cpp \
    libagchess/Position_MoveGen.cpp \
    libagchess/SAN.cpp \
    libagchess/SearchMask.cpp \
    libagchess/SimpleGame.cpp \
    libagchess/SimplePosition.cpp \
    libagchess/Square.cpp \
    libagchess/StandardChessGame.cpp \
    libagchess/StandardPosition.cpp \
    libagchess/TagPair.cpp \
    libagchess/chess_iterator.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    gui/chessboard.h \
    libagchess/AGChess_Common.h \
    libagchess/AGChess_Exception.h \
    libagchess/Bitboard.h \
    libagchess/Bitboard_MoveGen.h \
    libagchess/Board.h \
    libagchess/Board_MoveGen.h \
    libagchess/Color.h \
    libagchess/ColoredPiece.h \
    libagchess/DatabaseFilter.h \
    libagchess/EditablePosition.h \
    libagchess/FEN.h \
    libagchess/GameHeaders.h \
    libagchess/GameTree.h \
    libagchess/Move.h \
    libagchess/MoveTreeNode.h \
    libagchess/PGNDatabase.h \
    libagchess/PGNLexer.h \
    libagchess/Piece.h \
    libagchess/Position.h \
    libagchess/Position_MoveGen.h \
    libagchess/SAN.h \
    libagchess/SearchMask.h \
    libagchess/SimpleGame.h \
    libagchess/SimplePosition.h \
    libagchess/Square.h \
    libagchess/StandardChessGame.h \
    libagchess/StandardPosition.h \
    libagchess/StartPos.h \
    libagchess/TagPair.h \
    libagchess/Token.h \
    libagchess/chess_iterator.h \
    mainwindow.h

TRANSLATIONS += \
    ChessPgnReviser_en_GB.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \
    LICENSE.md \
    README.md
