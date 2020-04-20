#include "moveshistory.h"
#include <QLabel>
#include <QHeaderView>
#include <QPushButton>
#include <string>

loloof64::MovesHistory::MovesHistory(QWidget *parent) : QTableWidget(parent)
{
    setColumnCount(3);
    setHorizontalHeaderLabels(QStringList(QList<QString>{tr("Move number"), tr("White"), tr("Black")}));
    verticalHeader()->hide();
    verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader()->setDefaultSectionSize(36);
}

loloof64::MovesHistory::~MovesHistory()
{
    clearMoves();
}

void loloof64::MovesHistory::newGame(QString startPosition)
{
    _startPosition = startPosition;
    clearMoves();

    std::size_t current, previous = 0;
    char delim = ' ';
    current = startPosition.toStdString().find(delim);
    while (current != std::string::npos) {
        previous = current + 1;
        current = startPosition.toStdString().find(delim, previous);
    }
    auto moveNumberPart = startPosition.toStdString().substr(previous, current - previous);

    this->_moveNumber = std::stoi(moveNumberPart);
    addComponent(buildMoveNumber());
}

void loloof64::MovesHistory::addHistoryItem(HistoryItem *item, bool gameFinished)
{
    auto moveButton = new QPushButton(item->moveFan, this);
    moveButton->setFlat(true);
    moveButton->setStyleSheet("text-align: right; margin: 5px; font-size: 18px;");
    connect(moveButton, &QPushButton::clicked, [this, item](){
        emit requestPositionOnBoard(item);
    });
    _dataItems.push_back(item);
    addComponent(moveButton, gameFinished);
}

void loloof64::MovesHistory::clearMoves()
{
    setRowCount(0);

    for (auto it = _widgetsItems.rbegin(); it != _widgetsItems.rend(); ++it )
    {
        if (*it != nullptr)
        {
            delete *it;
            *it = nullptr;
        }
    }
    _widgetsItems.clear();

    for (auto it = _dataItems.rbegin(); it != _dataItems.rend(); ++it)
    {
        if (*it != nullptr)
        {
            delete *it;
            *it = nullptr;
        }
    }
    _dataItems.clear();

    _currentWorkingRow = -1;
    _currentWorkingCol = -1;

    _rowToHighlight = -1;
    _colToHighlight = -1;
}

void loloof64::MovesHistory::addComponent(QWidget *component, bool gameFinished)
{
    _widgetsItems.push_back(component);
    const auto notStarted = _currentWorkingCol < 0 && _currentWorkingRow < 0;

    if (notStarted)
    {
           insertRow(0);
           _currentWorkingCol = 0;
           _currentWorkingRow = 0;

           _rowToHighlight = _currentWorkingRow;
           _colToHighlight = _currentWorkingCol;

           setCellWidget(_currentWorkingRow, _currentWorkingCol, component);
           scrollToBottom();

           _currentWorkingCol++;
       }
       else
       {
           setCellWidget(_currentWorkingRow, _currentWorkingCol, component);
           _rowToHighlight = _currentWorkingRow;
           _colToHighlight = _currentWorkingCol;
           const auto isEndOfLine = _currentWorkingCol == 2;
           if (isEndOfLine && !gameFinished)
           {
               _moveNumber++;
               insertRow(_currentWorkingRow+1);

               _currentWorkingRow++;
               _currentWorkingCol = 0;
               auto *numberComponent = buildMoveNumber();
               _widgetsItems.push_back(numberComponent);
               setCellWidget(_currentWorkingRow, _currentWorkingCol, numberComponent);
               scrollToBottom();
           }
           else
           {
               scrollToBottom();
           }

           _currentWorkingCol++;

           setCurrentCell(_rowToHighlight, _colToHighlight);
       }
}

QLabel* loloof64::MovesHistory::buildMoveNumber()
{
    auto *numberComponent = new QLabel{QString(std::to_string(_moveNumber).c_str()), this};
    numberComponent->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    numberComponent->setMargin(5);
    auto font = QFont();
    font.setPointSize(18);
    numberComponent->setFont(QFont());

    scrollToBottom();
    return numberComponent;
}

void loloof64::MovesHistory::gotoFirstPosition()
{
    _colToHighlight = -1;
    _rowToHighlight = -1;

    emit requestPositionOnBoard(new HistoryItem(QString(), _startPosition, LastMoveCoordinates(-1, -1, -1, -1)));
}

void loloof64::MovesHistory::gotoLastPosition()
{
    auto oldColToHighlight = _colToHighlight;
    auto oldRowToHighlight = _rowToHighlight;

    _colToHighlight = _currentWorkingCol;
    _rowToHighlight = _currentWorkingRow;

    const auto item = itemToSet();
    const auto isValidItem = item != nullptr;
    if (isValidItem) emit requestPositionOnBoard(itemToSet());
    else {
        _colToHighlight = oldColToHighlight;
        _rowToHighlight = oldRowToHighlight;
    }
}

void loloof64::MovesHistory::gotoPreviousPosition()
{
    auto oldColToHighlight = _colToHighlight;
    auto oldRowToHighlight = _rowToHighlight;

    auto inACell = _colToHighlight >= 0 && _rowToHighlight >= 0;
    if (inACell) {
        if (_colToHighlight == 1)
        {
            _rowToHighlight--;
            _colToHighlight = 2;
        }
        else {
            _colToHighlight--;
        }
    }
    else {
        return;
    }

    const auto item = itemToSet();
    const auto isValidItem = item != nullptr;
    if (isValidItem) emit requestPositionOnBoard(itemToSet());
    else {
        _colToHighlight = oldColToHighlight;
        _rowToHighlight = oldRowToHighlight;
    }
}

void loloof64::MovesHistory::gotoNextPosition()
{
    auto oldColToHighlight = _colToHighlight;
    auto oldRowToHighlight = _rowToHighlight;

    auto inACell = _colToHighlight >= 0 && _rowToHighlight >= 0;
    if (inACell)
    {
        if (_colToHighlight == 2)
        {
            _rowToHighlight++;
            _colToHighlight = 1;
        }
        else {
            _colToHighlight++;
        }
    }
    else {
        _colToHighlight = 1;
        _rowToHighlight = 0;
    }

    const auto item = itemToSet();
    const auto isValidItem = item != nullptr;
    if (isValidItem) emit requestPositionOnBoard(itemToSet());
    else {
        _colToHighlight = oldColToHighlight;
        _rowToHighlight = oldRowToHighlight;
    }
}

void loloof64::MovesHistory::commitHistoryNodeSelection()
{
    auto stillInACell = _colToHighlight >= 0 && _rowToHighlight >= 0;
    if (stillInACell) {
        setCurrentCell(_rowToHighlight, _colToHighlight);
        //TODO scrollTo();
    }
    else
    {
        clearSelection();
        scrollToTop();
    }
}

loloof64::HistoryItem* loloof64::MovesHistory::itemToSet() const
{
    const auto itemIndex = 2*_rowToHighlight + (_colToHighlight - 1);
    const auto notPointingToAnItemData = itemIndex < 0 || itemIndex >= _dataItems.length();
    if (notPointingToAnItemData) return nullptr;
    return _dataItems[itemIndex];
}
