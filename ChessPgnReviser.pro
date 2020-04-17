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
    gui/chessboard/promotiondialog.cpp \
    gui/componentszone.cpp \
    gui/history/moveshistory.cpp \
    gui/mainwindow.cpp \
    libs/chessx-pgn/analysis.cpp \
    libs/chessx-pgn/arenabook.cpp \
    libs/chessx-pgn/bitboard.cpp \
    libs/chessx-pgn/board.cpp \
    libs/chessx-pgn/clipboarddatabase.cpp \
    libs/chessx-pgn/ctgbookwriter.cpp \
    libs/chessx-pgn/ctgdatabase.cpp \
    libs/chessx-pgn/database.cpp \
    libs/chessx-pgn/databaseconversion.cpp \
    libs/chessx-pgn/databaseinfo.cpp \
    libs/chessx-pgn/datesearch.cpp \
    libs/chessx-pgn/downloadmanager.cpp \
    libs/chessx-pgn/duplicatesearch.cpp \
    libs/chessx-pgn/ecoinfo.cpp \
    libs/chessx-pgn/ecopositions.cpp \
    libs/chessx-pgn/editaction.cpp \
    libs/chessx-pgn/elosearch.cpp \
    libs/chessx-pgn/engine.cpp \
    libs/chessx-pgn/enginedata.cpp \
    libs/chessx-pgn/enginelist.cpp \
    libs/chessx-pgn/engineoptiondata.cpp \
    libs/chessx-pgn/eventinfo.cpp \
    libs/chessx-pgn/ficsclient.cpp \
    libs/chessx-pgn/ficsdatabase.cpp \
    libs/chessx-pgn/filter.cpp \
    libs/chessx-pgn/filtermodel.cpp \
    libs/chessx-pgn/filtersearch.cpp \
    libs/chessx-pgn/game.cpp \
    libs/chessx-pgn/historylist.cpp \
    libs/chessx-pgn/index.cpp \
    libs/chessx-pgn/indexitem.cpp \
    libs/chessx-pgn/memorydatabase.cpp \
    libs/chessx-pgn/movedata.cpp \
    libs/chessx-pgn/nag.cpp \
    libs/chessx-pgn/numbersearch.cpp \
    libs/chessx-pgn/openingtree.cpp \
    libs/chessx-pgn/openingtreethread.cpp \
    libs/chessx-pgn/output.cpp \
    libs/chessx-pgn/outputoptions.cpp \
    libs/chessx-pgn/partialdate.cpp \
    libs/chessx-pgn/pdbtest.cpp \
    libs/chessx-pgn/pgndatabase.cpp \
    libs/chessx-pgn/piece.cpp \
    libs/chessx-pgn/playerdata.cpp \
    libs/chessx-pgn/playerdatabase.cpp \
    libs/chessx-pgn/playerinfo.cpp \
    libs/chessx-pgn/polyglotdatabase.cpp \
    libs/chessx-pgn/polyglotwriter.cpp \
    libs/chessx-pgn/positionsearch.cpp \
    libs/chessx-pgn/refcount.cpp \
    libs/chessx-pgn/result.cpp \
    libs/chessx-pgn/search.cpp \
    libs/chessx-pgn/settings.cpp \
    libs/chessx-pgn/spellchecker.cpp \
    libs/chessx-pgn/streamdatabase.cpp \
    libs/chessx-pgn/tablebase.cpp \
    libs/chessx-pgn/tags.cpp \
    libs/chessx-pgn/tagsearch.cpp \
    libs/chessx-pgn/telnetclient.cpp \
    libs/chessx-pgn/threadedguess.cpp \
    libs/chessx-pgn/uciengine.cpp \
    libs/chessx-pgn/wbengine.cpp \
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
    gui/mainwindow.h \
    libs/chessx-pgn/abk.h \
    libs/chessx-pgn/analysis.h \
    libs/chessx-pgn/arenabook.h \
    libs/chessx-pgn/bitboard.h \
    libs/chessx-pgn/bitfind.h \
    libs/chessx-pgn/board.h \
    libs/chessx-pgn/circularbuffer.h \
    libs/chessx-pgn/clipboarddatabase.h \
    libs/chessx-pgn/ctg.h \
    libs/chessx-pgn/ctgbookwriter.h \
    libs/chessx-pgn/ctgdatabase.h \
    libs/chessx-pgn/database.h \
    libs/chessx-pgn/databaseconversion.h \
    libs/chessx-pgn/databaseinfo.h \
    libs/chessx-pgn/datesearch.h \
    libs/chessx-pgn/downloadmanager.h \
    libs/chessx-pgn/duplicatesearch.h \
    libs/chessx-pgn/ecoinfo.h \
    libs/chessx-pgn/ecopositions.h \
    libs/chessx-pgn/editaction.h \
    libs/chessx-pgn/elosearch.h \
    libs/chessx-pgn/engine.h \
    libs/chessx-pgn/enginedata.h \
    libs/chessx-pgn/enginelist.h \
    libs/chessx-pgn/engineoptiondata.h \
    libs/chessx-pgn/engineparameter.h \
    libs/chessx-pgn/eventinfo.h \
    libs/chessx-pgn/ficsclient.h \
    libs/chessx-pgn/ficsdatabase.h \
    libs/chessx-pgn/filter.h \
    libs/chessx-pgn/filtermodel.h \
    libs/chessx-pgn/filteroperator.h \
    libs/chessx-pgn/filtersearch.h \
    libs/chessx-pgn/game.h \
    libs/chessx-pgn/gameid.h \
    libs/chessx-pgn/gameundocommand.h \
    libs/chessx-pgn/historylist.h \
    libs/chessx-pgn/index.h \
    libs/chessx-pgn/indexitem.h \
    libs/chessx-pgn/memorydatabase.h \
    libs/chessx-pgn/move.h \
    libs/chessx-pgn/movedata.h \
    libs/chessx-pgn/movelist.h \
    libs/chessx-pgn/nag.h \
    libs/chessx-pgn/numbersearch.h \
    libs/chessx-pgn/openingtree.h \
    libs/chessx-pgn/openingtreethread.h \
    libs/chessx-pgn/output.h \
    libs/chessx-pgn/outputoptions.h \
    libs/chessx-pgn/partialdate.h \
    libs/chessx-pgn/pdbtest.h \
    libs/chessx-pgn/pgndatabase.h \
    libs/chessx-pgn/piece.h \
    libs/chessx-pgn/playerdata.h \
    libs/chessx-pgn/playerdatabase.h \
    libs/chessx-pgn/playerinfo.h \
    libs/chessx-pgn/polyglotdatabase.h \
    libs/chessx-pgn/polyglotwriter.h \
    libs/chessx-pgn/positionsearch.h \
    libs/chessx-pgn/rand64.h \
    libs/chessx-pgn/refcount.h \
    libs/chessx-pgn/result.h \
    libs/chessx-pgn/search.h \
    libs/chessx-pgn/settings.h \
    libs/chessx-pgn/spellchecker.h \
    libs/chessx-pgn/square.h \
    libs/chessx-pgn/streamdatabase.h \
    libs/chessx-pgn/tablebase.h \
    libs/chessx-pgn/tags.h \
    libs/chessx-pgn/tagsearch.h \
    libs/chessx-pgn/tagvalues.h \
    libs/chessx-pgn/telnetclient.h \
    libs/chessx-pgn/threadedguess.h \
    libs/chessx-pgn/uciengine.h \
    libs/chessx-pgn/version.h \
    libs/chessx-pgn/wbengine.h \
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
    resources/icons/start.svg \
    resources/icons/swap.svg

RESOURCES += \
    resources.qrc \

