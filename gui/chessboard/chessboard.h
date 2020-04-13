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

    struct LastMoveCoordinates
    {
        explicit LastMoveCoordinates(int startFile, int startRank,
                                     int endFile, int endRank):
        startFile(startFile), startRank(startRank), endFile(endFile), endRank(endRank){}

        LastMoveCoordinates(const LastMoveCoordinates&) = delete;
        LastMoveCoordinates(const LastMoveCoordinates&&) = delete;

        int startFile, startRank, endFile, endRank;
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
        bool _gameInProgress;
        IPosition *_relatedPosition;
        DndData *_dndData;
        LastMoveCoordinates *_lastMoveCoordinates;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
    };
}

#endif // CHESSBOARD_H
