#ifndef GAMESELECTIONMAINZONE_H
#define GAMESELECTIONMAINZONE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include "../chessboard/chessboard.h"

namespace loloof64 {
    class GameSelectionMainZone : public QWidget
    {
        Q_OBJECT
    public:
        explicit GameSelectionMainZone(QWidget *parent = nullptr);
        ~GameSelectionMainZone();

    signals:

    private:
        QHBoxLayout *_layout;
        QPushButton *_goFirstButton;
        QPushButton *_goPreviousButton;
        QPushButton *_goNextButton;
        QPushButton *_goLastButton;
        ChessBoard *_board;
    };
};

#endif // GAMESELECTIONMAINZONE_H
