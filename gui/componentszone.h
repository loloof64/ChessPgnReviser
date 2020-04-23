#ifndef COMPONENTSZONE_H
#define COMPONENTSZONE_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QVector>
#include <QFrame>
#include <QScrollArea>
#include <QListWidget>
#include <QPushButton>
#include <QList>
#include "chessboard/chessboard.h"
#include "history/moveshistoryfullcomponent.h"
#include "../libs/chessx-pgn/database/pgndatabase.h"
#include "./game_selection/gameselectiondialog.h"

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
        QList<QString> _expectedMovesFanList;
        QHBoxLayout *_mainLayout;
        ChessBoard *_chessBoard;
        MovesHistoryFullComponent *_movesHistory;
        QScrollArea *_variantSelectionZone;
        QVBoxLayout *_variantSelectionZoneLayout;
        QFrame *_variantSelectionZoneWidget;
        QLabel *_variantSelectionZoneLabel;
        QListWidget *_variantMainButton;
        QListWidget *_variantVariantsButtons;
        PgnDatabase *_pgnDatabase;
        GameSelectionDialog *_gameSelectionDialog;
        Game _currentGame;
        bool _isWhitePly;

        void handleMoveVerification(MoveCoordinates moveCoordinates, char promotion = 0);
        void makeComputerPlayNextMove();
        void showLoosingMessage();
        char promotionPieceToPromotionFen(Piece promotion) const;
        void clearVariants();
        void updateExpectedMoves();
        QString moveToMoveFan(Move moveId);
    };
}

#endif // COMPONENTSZONE_H
