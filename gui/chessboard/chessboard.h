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

        int startFile, startRank, endFile, endRank;
    };

    class ChessBoard : public QWidget
    {
        Q_OBJECT
    public:
        explicit ChessBoard(int cellsSize, QWidget *parent = nullptr);
        ~ChessBoard();
        inline bool gameInProgress(){ return _gameInProgress; }

    signals:
        // a move has been made
        // 1st parameter: the move san (QString)
        // 2nd parameter: the resulting position fen (QString)
        // 3rd parameter: the move coordinates (LastMoveCoordinates)
        void moveDoneAsSan(QString, QString, LastMoveCoordinates);

        // a move has been made
        // 1st parameter: the move fan (QString)
        // 2nd parameter: the resulting position fen (QString)
        // 3rd parameter: the move coordinates (LastMoveCoordinates)
        void moveDoneAsFan(QString, QString, LastMoveCoordinates);

    public slots:
        void reverse();
        void newGame();
        void stopGame();

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
