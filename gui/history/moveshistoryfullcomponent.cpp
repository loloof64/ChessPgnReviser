#include "moveshistoryfullcomponent.h"

loloof64::MovesHistoryFullComponent::MovesHistoryFullComponent(QWidget *parent): QWidget(parent)
{
    _mainLayout = new QVBoxLayout(this);
    _historyZone = new MovesHistory(this);

    setLayout(_mainLayout);
    _mainLayout->addWidget(_historyZone);
}

loloof64::MovesHistoryFullComponent::~MovesHistoryFullComponent()
{
    delete _historyZone;
    delete _mainLayout;
}

void loloof64::MovesHistoryFullComponent::newGame(int moveNumber)
{
    _historyZone->newGame(moveNumber);
}

void loloof64::MovesHistoryFullComponent::addHistoryItem(HistoryItem *item, bool gameFinished)
{
    _historyZone->addHistoryItem(item, gameFinished);
}

loloof64::MovesHistory* loloof64::MovesHistoryFullComponent::getMovesHistoryMainComponent() const
{
    return _historyZone;
}
