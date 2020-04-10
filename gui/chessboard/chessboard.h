#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include "IPosition.h"

namespace loloof64 {
    class ChessBoard : public QWidget
    {
        Q_OBJECT
    public:
        explicit ChessBoard(int cellsSize, QWidget *parent);
        ~ChessBoard();

    signals:

    protected:
        void paintEvent(QPaintEvent *event) override;

    private:
        int _cellsSize;
        IPosition *_relatedPosition;
    };
}

#endif // CHESSBOARD_H
