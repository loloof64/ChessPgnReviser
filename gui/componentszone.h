#ifndef COMPONENTSZONE_H
#define COMPONENTSZONE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVector>
#include "chessboard/chessboard.h"
#include "history/moveshistoryfullcomponent.h"
#include "../libs/chessx-pgn/database/pgndatabase.h"
#include "./game_selection/gameselectiondialog.h"
#include "./variantmovechooserdialog.h"

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
        ChessBoard *_chessBoard;
        MovesHistoryFullComponent *_movesHistory;
        PgnDatabase *_pgnDatabase;
        GameSelectionDialog *_gameSelectionDialog;
        VariantMoveChooserDialog *_moveSelectionDialog;
        Game _currentGame;
        bool _isWhitePly;

        void handleMoveVerification(MoveCoordinates moveCoordinates, char promotion = 0);
        void makeComputerPlayNextMove();
        void showLoosingMessage();
        char promotionPieceToPromotionFen(Piece promotion) const;
    };
}

#endif // COMPONENTSZONE_H
