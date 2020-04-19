#include "moveshistoryfullcomponent.h"

loloof64::MovesHistoryFullComponent::MovesHistoryFullComponent(QWidget *parent): QWidget(parent)
{
    _mainLayout = new QVBoxLayout(this);
    _historyZone = new MovesHistory(this);
    _buttonsZone = new MovesHistoryButtons(this);

    setLayout(_mainLayout);
    _mainLayout->addWidget(_buttonsZone);
    _mainLayout->addWidget(_historyZone);
}

loloof64::MovesHistoryFullComponent::~MovesHistoryFullComponent()
{
    delete _buttonsZone;
    delete _historyZone;
    delete _mainLayout;
}

void loloof64::MovesHistoryFullComponent::newGame(QString startPosition)
{
    _historyZone->newGame(startPosition);
}

void loloof64::MovesHistoryFullComponent::addHistoryItem(HistoryItem *item, bool gameFinished)
{
    _historyZone->addHistoryItem(item, gameFinished);
}

loloof64::MovesHistory* loloof64::MovesHistoryFullComponent::getMovesHistoryMainComponent() const
{
    return _historyZone;
}

loloof64::MovesHistoryButtons* loloof64::MovesHistoryFullComponent::getButtonsZone() const
{
    return _buttonsZone;
}
