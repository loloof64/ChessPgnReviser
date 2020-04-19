#ifndef MOVESHISTORYFULLCOMPONENT_H
#define MOVESHISTORYFULLCOMPONENT_H

#include <QWidget>
#include <QVBoxLayout>
#include "moveshistory.h"

namespace loloof64 {
    class MovesHistoryFullComponent: public QWidget
    {
    Q_OBJECT
    public:
        MovesHistoryFullComponent(QWidget *parent = nullptr);
        ~MovesHistoryFullComponent();

        MovesHistory* getMovesHistoryMainComponent() const;

        void newGame(int moveNumber = 1);
        void addHistoryItem(HistoryItem *item, bool gameFinished = false);
    private:
        QVBoxLayout *_mainLayout;
        MovesHistory *_historyZone;
    };
}

#endif // MOVESHISTORYFULLCOMPONENT_H
