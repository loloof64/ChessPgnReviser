#ifndef MOVESHISTORYFULLCOMPONENT_H
#define MOVESHISTORYFULLCOMPONENT_H

#include <QWidget>
#include <QVBoxLayout>
#include "moveshistory.h"
#include "moveshistorybuttons.h"

namespace loloof64 {
    class MovesHistoryFullComponent: public QWidget
    {
    Q_OBJECT
    public:
        MovesHistoryFullComponent(QWidget *parent = nullptr);
        ~MovesHistoryFullComponent();

        MovesHistory* getMovesHistoryMainComponent() const;
        MovesHistoryButtons* getButtonsZone() const;

        void newGame(QString startPosition);
        void addHistoryItem(HistoryItem *item, bool gameFinished = false);
    private:
        QVBoxLayout *_mainLayout;
        MovesHistory *_historyZone;
        MovesHistoryButtons *_buttonsZone;
    };
}

#endif // MOVESHISTORYFULLCOMPONENT_H
