#ifndef MOVESHISTORY_H
#define MOVESHISTORY_H

#include <QTableWidget>
#include <QVector>
#include <QLabel>
#include "../chessboard/IPosition.h"

namespace loloof64 {
    struct HistoryCellCoordinates
    {
        HistoryCellCoordinates(int col, int row): col(col), row(row){}
        int col;
        int row;
    };

    class MovesHistory : public QTableWidget
    {
        Q_OBJECT
    public:
        explicit MovesHistory(QWidget *parent = nullptr);
        ~MovesHistory();
        void newGame(QString startPosition);
        void addHistoryItem(HistoryItem *item, bool gameFinished = false);

        void gotoFirstPosition();
        void gotoLastPosition();
        void gotoPreviousPosition();
        void gotoNextPosition();

        void commitPositionRequest();
        void clearPositionRequest();
    signals:
        void requestPositionOnBoard(HistoryItem *item);
    private:
        HistoryCellCoordinates *_cellToUpdate;
        QString _startPosition;
        int _moveNumber{1};
        int _currentRow{-1}, _currentCol{-1};
        QVector<QWidget *> _widgetsItems;
        QVector<HistoryItem *> _dataItems;
        void clearMoves();
        void addComponent(QWidget *component, bool gameFinished = false);
        QLabel *buildMoveNumber();
    };
}

#endif // MOVESHISTORY_H
