#ifndef MOVESHISTORY_H
#define MOVESHISTORY_H

#include <QTableWidget>
#include <QVector>
#include <QLabel>

namespace loloof64 {
    class MovesHistory : public QTableWidget
    {
        Q_OBJECT
    public:
        explicit MovesHistory(QWidget *parent = nullptr);
        ~MovesHistory();
        void newGame(int moveNumber = 1);
        void addMoveFan(QString moveFan);
    private:
        int currentRow{-1}, currentCol{-1};
        QVector<QWidget *> items;
        void clearMoves();
        void addComponent(QWidget *component);
        QLabel *buildMoveNumber(int moveNumber);
    };
}

#endif // MOVESHISTORY_H
