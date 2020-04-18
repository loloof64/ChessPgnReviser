#ifndef COMPONENTSZONE_H
#define COMPONENTSZONE_H

#include <QWidget>
#include <QHBoxLayout>
#include "chessboard/chessboard.h"
#include "history/moveshistory.h"
#include "../libs/chessx-pgn/database/pgndatabase.h"

namespace loloof64 {
    class ComponentsZone : public QWidget
    {
        Q_OBJECT
    public:
        explicit ComponentsZone(QWidget *parent = nullptr);
        ~ComponentsZone();
        inline bool gameInProgress(){ return _chessBoard->gameInProgress(); }

    public slots:
        void reverseBoard();
        void newGame();
        void stopGame();

    private:
        QHBoxLayout *_mainLayout;
        loloof64::ChessBoard *_chessBoard;
        loloof64::MovesHistory *_movesHistory;
        PgnDatabase _pgnDatabase;
        Game _currentGame;
        bool _isWhitePly;

        void handleMoveVerification(QString moveSan);
    };
}

#endif // COMPONENTSZONE_H
