#include "moveshistory.h"
#include <QLabel>
#include <QHeaderView>
#include <QFont>
#include <QPushButton>
#include <string>
#include <QPainter>

loloof64::MovesHistory::MovesHistory(QWidget *parent) : QWidget(parent)
{
    _mainLayout = new FlowLayout(this, 10, 10, 10);
    setLayout(_mainLayout);

    setStyleSheet("background-color: white");
    setMinimumSize(360, 400);
}

loloof64::MovesHistory::~MovesHistory()
{
    clearMoves();
    delete _mainLayout;
}

void loloof64::MovesHistory::newGame(QString startPosition)
{
    _itemToHighlightIndex = -1;
    _startPosition = startPosition;
    clearMoves();

    const auto parts = startPosition.split(" ");
    auto moveNumberPart = parts[5];
    _blackToMoveFirst = parts[1] == "b";
    _nextMoveIsForBlack = _blackToMoveFirst;

    _moveNumber = std::stoi(moveNumberPart.toStdString());
    auto moveNumberComponent = buildMoveNumber();
    _mainLayout->addWidget(moveNumberComponent);
    _widgetsItems.push_back(moveNumberComponent);
    _dataItems.push_back(HistoryItem("", "", MoveCoordinates(-1,-1,-1,-1)));

    updateItemHighlightingTo(0);
}

void loloof64::MovesHistory::addHistoryItem(HistoryItem item, bool gameFinished)
{
    auto moveButton = new QPushButton(item.moveFan, this);
    //moveButton->setFlat(true);
    moveButton->setStyleSheet("margin: 0px 5px; font-size: 22px;");
    moveButton->setFont(QFont("Free Serif"));

    connect(moveButton, &QPushButton::clicked, [this, item](){
        auto itemIndex = _dataItems.indexOf(item);
        _pendingNodeSelectionIndex = itemIndex;
        _hasPendingNodeSelection = true;
        emit requestPositionOnBoard(item);
    });

    addMoveComponent(moveButton, item, gameFinished);
}

void loloof64::MovesHistory::clearMoves()
{

    for (auto it = _widgetsItems.rbegin(); it != _widgetsItems.rend(); ++it )
    {
        if (*it != nullptr)
        {
            delete *it;
            *it = nullptr;
        }
    }
    _widgetsItems.clear();
    _dataItems.clear();
}

void loloof64::MovesHistory::addMoveComponent(QPushButton *moveComponent, HistoryItem item, bool gameFinished)
{
    _pendingNodeSelectionIndex = -1;
    _hasPendingNodeSelection = false;

   auto needToAddMoveNumber =  (_blackToMoveFirst && ! _nextMoveIsForBlack && _mainLayout->count() > 1)
            || (! _blackToMoveFirst && _nextMoveIsForBlack && _mainLayout->count() > 1);
   _mainLayout->addWidget(moveComponent);
   _widgetsItems.push_back(moveComponent);
   _dataItems.push_back(item);
   updateItemHighlightingTo(_widgetsItems.size() - 1);

   if (needToAddMoveNumber && !gameFinished)
   {
       _moveNumber++;

       auto *numberComponent = buildMoveNumber();
       _mainLayout->addWidget(numberComponent);
       _widgetsItems.push_back(numberComponent);
       _dataItems.push_back(HistoryItem("", "", MoveCoordinates(-1,-1,-1,-1)));
   }
   emit scrollToSelectedItemRequest(_itemToHighlightIndex);

   _nextMoveIsForBlack = ! _nextMoveIsForBlack;
}

QLabel* loloof64::MovesHistory::buildMoveNumber()
{
    auto numberText = QString(std::to_string(_moveNumber).c_str());
    numberText += ".";
    auto isFirstMoveAndForBlack = _blackToMoveFirst && _mainLayout->count() == 0;
    if (isFirstMoveAndForBlack) numberText += "..";

    auto *numberComponent = new QLabel{numberText, this};
    auto font = QFont();
    font.setPixelSize(22);
    font.setFamily("Free Serif");
    numberComponent->setFont(font);

    return numberComponent;
}

void loloof64::MovesHistory::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void loloof64::MovesHistory::updateItemHighlightingTo(int newItemToHighlightIndex)
{
    // Clearing current highlighting if necessary
    if (_itemToHighlightIndex >= 0)
    {
        auto wigdetToUpdate = _widgetsItems[_itemToHighlightIndex];
        wigdetToUpdate->setStyleSheet("QPushButton { background-color: white; margin: 0px 5px; font-size: 22px; }");
    }

    _itemToHighlightIndex = newItemToHighlightIndex;

    // Setting current highlighting if possible
    if (_itemToHighlightIndex >= 0)
    {
        auto wigdetToUpdate = _widgetsItems[_itemToHighlightIndex];
        wigdetToUpdate->setStyleSheet("QPushButton { background-color: #70d123; margin: 0px 5px; font-size: 22px; }");
    }
}

void loloof64::MovesHistory::gotoFirstPosition()
{
    _pendingNodeSelectionIndex = -1;
    _hasPendingNodeSelection = true;

    emit requestPositionOnBoard(HistoryItem(QString(), _startPosition, MoveCoordinates(-1, -1, -1, -1)));
}

void loloof64::MovesHistory::gotoPreviousPosition()
{
    // Searching backward for the first QPushButton, until first node if not found.
    for (_pendingNodeSelectionIndex = _itemToHighlightIndex - 1; _pendingNodeSelectionIndex >= 0; --_pendingNodeSelectionIndex)
    {
        auto currentWidget = _widgetsItems[_pendingNodeSelectionIndex];
        auto isAButton = dynamic_cast<QPushButton *>(currentWidget) != nullptr;

        if(isAButton) {
            _hasPendingNodeSelection = true;
            emit requestPositionOnBoard(_dataItems[_pendingNodeSelectionIndex]);
            return;
        }
    }

    _hasPendingNodeSelection = true;
    emit requestPositionOnBoard(HistoryItem("", _startPosition, MoveCoordinates(-1,-1,-1,-1)));
}

void loloof64::MovesHistory::gotoNextPosition()
{
    // Searching forward for the first QPushButton, until no node left.
    for (_pendingNodeSelectionIndex = _itemToHighlightIndex + 1; _pendingNodeSelectionIndex < _dataItems.size(); ++_pendingNodeSelectionIndex)
    {
        auto currentWidget = _widgetsItems[_pendingNodeSelectionIndex];
        auto isAButton = dynamic_cast<QPushButton *>(currentWidget) != nullptr;

        if(isAButton) {
            _hasPendingNodeSelection = true;
            emit requestPositionOnBoard(_dataItems[_pendingNodeSelectionIndex]);
            return;
        }
    }

    // Nothing to do otherwise, in order cancelling the process.
}

void loloof64::MovesHistory::gotoLastPosition()
{
    // Searching backward from the last item for the first QPushButton, until no node left.
    for (_pendingNodeSelectionIndex = _dataItems.size() - 1; _pendingNodeSelectionIndex >= 0; --_pendingNodeSelectionIndex)
    {
        auto currentWidget = _widgetsItems[_pendingNodeSelectionIndex];
        auto isAButton = dynamic_cast<QPushButton *>(currentWidget) != nullptr;

        if(isAButton) {
            _hasPendingNodeSelection = true;
            emit requestPositionOnBoard(_dataItems[_pendingNodeSelectionIndex]);
            return;
        }
    }

    // Nothing to do otherwise, in order cancelling the process.
}

void loloof64::MovesHistory::commitHistoryNodeSelection()
{
    if (_hasPendingNodeSelection)
    {
        if (_pendingNodeSelectionIndex < 0)
        {
            updateItemHighlightingTo(-1);
        }
        else
        {
            updateItemHighlightingTo(_pendingNodeSelectionIndex);
        }

        _pendingNodeSelectionIndex = -1;
        _hasPendingNodeSelection = false;
    }

    emit scrollToSelectedItemRequest(_itemToHighlightIndex);
}
