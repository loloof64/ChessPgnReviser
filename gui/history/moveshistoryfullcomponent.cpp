#include "moveshistoryfullcomponent.h"

loloof64::MovesHistoryFullComponent::MovesHistoryFullComponent(QWidget *parent): QWidget(parent)
{
    _mainLayout = new QVBoxLayout(this);
    _buttonsZone = new MovesHistoryButtons(this);
    _mainZoneScrollArea = new QScrollArea(this);
    _historyZone = new MovesHistory();

    setLayout(_mainLayout);
    _mainLayout->addWidget(_buttonsZone);
    _mainLayout->addWidget(_mainZoneScrollArea);

    _mainZoneScrollArea->setWidget(_historyZone);
    _mainZoneScrollArea->setWidgetResizable( true );

    connect(_historyZone, &MovesHistory::scrollToSelectedItemRequest, [this](int requestedIndex) {
        if (requestedIndex > 0)
        {
            const auto ITEMS_MEDIUM_WIDTH = 100;
            const auto ITEMS_MEDIUM_HEIGHT = 35;
            auto line = requestedIndex / 4;
            auto column = requestedIndex % 4;
            _mainZoneScrollArea->ensureVisible(ITEMS_MEDIUM_WIDTH*column, ITEMS_MEDIUM_HEIGHT*line);
        }
        else
        {
            _mainZoneScrollArea->ensureVisible(0, 0);
        }
    });
}

loloof64::MovesHistoryFullComponent::~MovesHistoryFullComponent()
{
    delete _historyZone;
    delete _mainZoneScrollArea;
    delete _buttonsZone;
    delete _mainLayout;
}

void loloof64::MovesHistoryFullComponent::newGame(QString startPosition)
{
    _historyZone->newGame(startPosition);
}

void loloof64::MovesHistoryFullComponent::addHistoryItem(HistoryItem item, bool gameFinished)
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

void loloof64::MovesHistoryFullComponent::commitHistoryNodeSelection()
{
    _historyZone->commitHistoryNodeSelection();
}
