QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += USE_C11

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gui/adapters/thcposition.cpp \
    gui/chessboard/chessboard.cpp \
    gui/chessboard/promotiondialog.cpp \
    gui/componentszone.cpp \
    gui/history/moveshistory.cpp \
    gui/history/moveshistorybuttons.cpp \
    gui/history/moveshistoryfullcomponent.cpp \
    gui/mainwindow.cpp \
    libs/chessx-pgn/database/analysis.cpp \
    libs/chessx-pgn/database/arenabook.cpp \
    libs/chessx-pgn/database/bitboard.cpp \
    libs/chessx-pgn/database/board.cpp \
    libs/chessx-pgn/database/clipboarddatabase.cpp \
    libs/chessx-pgn/database/ctgbookwriter.cpp \
    libs/chessx-pgn/database/ctgdatabase.cpp \
    libs/chessx-pgn/database/database.cpp \
    libs/chessx-pgn/database/databaseconversion.cpp \
    libs/chessx-pgn/database/databaseinfo.cpp \
    libs/chessx-pgn/database/datesearch.cpp \
    libs/chessx-pgn/database/duplicatesearch.cpp \
    libs/chessx-pgn/database/ecoinfo.cpp \
    libs/chessx-pgn/database/ecopositions.cpp \
    libs/chessx-pgn/database/editaction.cpp \
    libs/chessx-pgn/database/elosearch.cpp \
    libs/chessx-pgn/database/engineoptiondata.cpp \
    libs/chessx-pgn/database/eventinfo.cpp \
    libs/chessx-pgn/database/filter.cpp \
    libs/chessx-pgn/database/filtermodel.cpp \
    libs/chessx-pgn/database/filtersearch.cpp \
    libs/chessx-pgn/database/game.cpp \
    libs/chessx-pgn/database/historylist.cpp \
    libs/chessx-pgn/database/index.cpp \
    libs/chessx-pgn/database/indexitem.cpp \
    libs/chessx-pgn/database/memorydatabase.cpp \
    libs/chessx-pgn/database/movedata.cpp \
    libs/chessx-pgn/database/nag.cpp \
    libs/chessx-pgn/database/numbersearch.cpp \
    libs/chessx-pgn/database/openingtreethread.cpp \
    libs/chessx-pgn/database/partialdate.cpp \
    libs/chessx-pgn/database/pdbtest.cpp \
    libs/chessx-pgn/database/pgndatabase.cpp \
    libs/chessx-pgn/database/piece.cpp \
    libs/chessx-pgn/database/playerdata.cpp \
    libs/chessx-pgn/database/playerdatabase.cpp \
    libs/chessx-pgn/database/playerinfo.cpp \
    libs/chessx-pgn/database/polyglotdatabase.cpp \
    libs/chessx-pgn/database/polyglotwriter.cpp \
    libs/chessx-pgn/database/positionsearch.cpp \
    libs/chessx-pgn/database/refcount.cpp \
    libs/chessx-pgn/database/result.cpp \
    libs/chessx-pgn/database/search.cpp \
    libs/chessx-pgn/database/streamdatabase.cpp \
    libs/chessx-pgn/database/tags.cpp \
    libs/chessx-pgn/database/tagsearch.cpp \
    libs/chessx-pgn/database/threadedguess.cpp \
    libs/chessx-pgn/guess/compileeco.cpp \
    libs/chessx-pgn/guess/guess.cpp \
    libs/chessx-pgn/guess/guessengine.cpp \
    libs/chessx-pgn/guess/misc.cpp \
    libs/chessx-pgn/guess/movelist.cpp \
    libs/chessx-pgn/guess/position.cpp \
    libs/chessx-pgn/guess/recog.cpp \
    libs/thc-chess-library/ChessPosition.cpp \
    libs/thc-chess-library/ChessRules.cpp \
    libs/thc-chess-library/Move.cpp \
    libs/thc-chess-library/PrivateChessDefs.cpp \
    libs/thc-chess-library/util.cpp \
    main.cpp \

HEADERS += \
    gui/adapters/thcposition.h \
    gui/chessboard/IPosition.h \
    gui/chessboard/chessboard.h \
    gui/chessboard/promotiondialog.h \
    gui/componentszone.h \
    gui/history/moveshistory.h \
    gui/history/moveshistorybuttons.h \
    gui/history/moveshistoryfullcomponent.h \
    gui/mainwindow.h \
    libs/chessx-pgn/database/abk.h \
    libs/chessx-pgn/database/analysis.h \
    libs/chessx-pgn/database/arenabook.h \
    libs/chessx-pgn/database/bitboard.h \
    libs/chessx-pgn/database/bitfind.h \
    libs/chessx-pgn/database/board.h \
    libs/chessx-pgn/database/circularbuffer.h \
    libs/chessx-pgn/database/clipboarddatabase.h \
    libs/chessx-pgn/database/ctg.h \
    libs/chessx-pgn/database/ctgbookwriter.h \
    libs/chessx-pgn/database/ctgdatabase.h \
    libs/chessx-pgn/database/database.h \
    libs/chessx-pgn/database/databaseconversion.h \
    libs/chessx-pgn/database/databaseinfo.h \
    libs/chessx-pgn/database/datesearch.h \
    libs/chessx-pgn/database/duplicatesearch.h \
    libs/chessx-pgn/database/ecoinfo.h \
    libs/chessx-pgn/database/ecopositions.h \
    libs/chessx-pgn/database/editaction.h \
    libs/chessx-pgn/database/elosearch.h \
    libs/chessx-pgn/database/engineoptiondata.h \
    libs/chessx-pgn/database/engineparameter.h \
    libs/chessx-pgn/database/eventinfo.h \
    libs/chessx-pgn/database/filter.h \
    libs/chessx-pgn/database/filtermodel.h \
    libs/chessx-pgn/database/filteroperator.h \
    libs/chessx-pgn/database/filtersearch.h \
    libs/chessx-pgn/database/game.h \
    libs/chessx-pgn/database/gameid.h \
    libs/chessx-pgn/database/gameundocommand.h \
    libs/chessx-pgn/database/historylist.h \
    libs/chessx-pgn/database/index.h \
    libs/chessx-pgn/database/indexitem.h \
    libs/chessx-pgn/database/memorydatabase.h \
    libs/chessx-pgn/database/move.h \
    libs/chessx-pgn/database/movedata.h \
    libs/chessx-pgn/database/movelist.h \
    libs/chessx-pgn/database/nag.h \
    libs/chessx-pgn/database/numbersearch.h \
    libs/chessx-pgn/database/openingtreethread.h \
    libs/chessx-pgn/database/partialdate.h \
    libs/chessx-pgn/database/pdbtest.h \
    libs/chessx-pgn/database/pgndatabase.h \
    libs/chessx-pgn/database/piece.h \
    libs/chessx-pgn/database/playerdata.h \
    libs/chessx-pgn/database/playerdatabase.h \
    libs/chessx-pgn/database/playerinfo.h \
    libs/chessx-pgn/database/polyglotdatabase.h \
    libs/chessx-pgn/database/polyglotwriter.h \
    libs/chessx-pgn/database/positionsearch.h \
    libs/chessx-pgn/database/rand64.h \
    libs/chessx-pgn/database/refcount.h \
    libs/chessx-pgn/database/result.h \
    libs/chessx-pgn/database/search.h \
    libs/chessx-pgn/database/square.h \
    libs/chessx-pgn/database/streamdatabase.h \
    libs/chessx-pgn/database/tags.h \
    libs/chessx-pgn/database/tagsearch.h \
    libs/chessx-pgn/database/tagvalues.h \
    libs/chessx-pgn/database/threadedguess.h \
    libs/chessx-pgn/database/version.h \
    libs/chessx-pgn/guess/attacks.h \
    libs/chessx-pgn/guess/common.h \
    libs/chessx-pgn/guess/compileeco.h \
    libs/chessx-pgn/guess/error.h \
    libs/chessx-pgn/guess/guess.h \
    libs/chessx-pgn/guess/guessengine.h \
    libs/chessx-pgn/guess/hash.h \
    libs/chessx-pgn/guess/misc.h \
    libs/chessx-pgn/guess/movelist.h \
    libs/chessx-pgn/guess/position.h \
    libs/chessx-pgn/guess/recog.h \
    libs/chessx-pgn/guess/sqlist.h \
    libs/chessx-pgn/guess/sqmove.h \
    libs/chessx-pgn/guess/sqset.h \
    libs/thc-chess-library/ChessDefs.h \
    libs/thc-chess-library/ChessPosition.h \
    libs/thc-chess-library/ChessPositionRaw.h \
    libs/thc-chess-library/ChessRules.h \
    libs/thc-chess-library/DebugPrintf.h \
    libs/thc-chess-library/GeneratedLookupTables.h \
    libs/thc-chess-library/HashLookup.h \
    libs/thc-chess-library/Move.h \
    libs/thc-chess-library/PrivateChessDefs.h \
    libs/thc-chess-library/util.h

TRANSLATIONS += \
    translations/ChessPgnReviser.en.ts \
    translations/ChessPgnReviser.fr.ts \
    translations/ChessPgnReviser.es.ts

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
    resources/icons/left-arrow.svg \
    resources/icons/next.svg \
    resources/icons/previous.svg \
    resources/icons/right-arrow.svg \
    resources/icons/start.svg \
    resources/icons/stop.svg \
    resources/icons/swap.svg

RESOURCES += \
    resources.qrc \

