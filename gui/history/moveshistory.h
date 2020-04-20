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
        void newGame(QString startPosition);
        void addHistoryItem(HistoryItem *item, bool gameFinished = false);

        void gotoFirstPosition();
        void gotoLastPosition();
        void gotoPreviousPosition();
        void gotoNextPosition();

        void commitHistoryNodeSelection();
    signals:
        void requestPositionOnBoard(HistoryItem *item);
    private:
        QString _startPosition;
        int _moveNumber{1};
        int _currentWorkingRow{-1}, _currentWorkingCol{-1};
        int _rowToHighlight{-1}, _colToHighlight{-1};
        QVector<QWidget *> _widgetsItems;
        QVector<HistoryItem *> _dataItems;
        void clearMoves();
        void addComponent(QWidget *component, bool gameFinished = false);
        HistoryItem* itemToSet() const;
        QLabel *buildMoveNumber();
    };
}

#endif // MOVESHISTORY_H
