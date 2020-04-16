#ifndef MOVESHISTORY_H
#define MOVESHISTORY_H

#include <QTableWidget>
#include <QVector>
#include <QLabel>
#include "../chessboard/IPosition.h"

namespace loloof64 {
    class MovesHistory : public QTableWidget
    {
        Q_OBJECT
    public:
        explicit MovesHistory(QWidget *parent = nullptr);
        ~MovesHistory();
        void newGame(int moveNumber = 1);
        void addHistoryItem(HistoryItem *item);
    signals:
        void requestPositionOnBoard(HistoryItem *item);
    private:
        int _moveNumber{1};
        int _currentRow{-1}, _currentCol{-1};
        QVector<QWidget *> _widgetsItems;
        QVector<HistoryItem *> _dataItems;
        void clearMoves();
        void addComponent(QWidget *component);
        QLabel *buildMoveNumber();
    };
}

#endif // MOVESHISTORY_H
