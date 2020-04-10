#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include "IPosition.h"

namespace loloof64 {
    class ChessBoard : public QWidget
    {
        Q_OBJECT
    public:
        explicit ChessBoard(int cellsSize, QWidget *parent = nullptr);
        ~ChessBoard();

    public slots:
        void reverse();

    protected:
        void paintEvent(QPaintEvent *event) override;

    private:
        int _cellsSize;
        bool _reversed;
        IPosition *_relatedPosition;
    };
}

#endif // CHESSBOARD_H
