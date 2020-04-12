#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QMouseEvent>
#include "IPosition.h"

namespace loloof64 {
    struct DndData
    {
        explicit DndData(char pieceFen, int startFile, int startRank,
                         int pieceX, int pieceY):
            pieceFen(pieceFen), pointerInBounds(false), startFile(startFile), startRank(startRank),
            pieceX(pieceX), pieceY(pieceY){};
        DndData(const DndData&) = delete;
        DndData(const DndData&&) = delete;
        char pieceFen;
        bool pointerInBounds;
        int startFile, startRank;
        int endFile, endRank;
        int pieceX, pieceY;
    };

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
        DndData *_dndData;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
    };
}

#endif // CHESSBOARD_H
