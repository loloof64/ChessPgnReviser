#ifndef GAMESELECTIONMAINZONE_H
#define GAMESELECTIONMAINZONE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include "../chessboard/chessboard.h"
#include "../../libs/chessx-pgn/database/pgndatabase.h"

namespace loloof64 {
    class GameSelectionMainZone : public QWidget
    {
        Q_OBJECT
    public:
        explicit GameSelectionMainZone(QWidget *parent = nullptr);
        ~GameSelectionMainZone();
        void setPgnDatabase(PgnDatabase *database);

    signals:

    private:
        quint64 _selectedGameIndex;
        QHBoxLayout *_layout;
        QPushButton *_goFirstButton;
        QPushButton *_goPreviousButton;
        QPushButton *_goNextButton;
        QPushButton *_goLastButton;
        ChessBoard *_board;

        // Not to be released in the destructor, just borrowed
        PgnDatabase *_pgnDatabase;
        Game _currentBaseGame;

        void loadGameStart();
    };
};

#endif // GAMESELECTIONMAINZONE_H
