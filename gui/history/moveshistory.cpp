#include "moveshistory.h"
#include <QLabel>
#include <QHeaderView>
#include <QPushButton>
#include <string>

loloof64::MovesHistory::MovesHistory(QWidget *parent) : QTableWidget(parent)
{
    _cellToUpdate = nullptr;
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

    for (auto it = _dataItems.rbegin(); it != _dataItems.rend(); ++it)
    {
        if (*it != nullptr)
        {
            delete *it;
            *it = nullptr;
        }
    }

    _currentRow = -1;
    _currentCol = -1;
    _cellToUpdate = nullptr;
}

void loloof64::MovesHistory::addComponent(QWidget *component, bool gameFinished)
{
    _widgetsItems.push_back(component);
    const auto notStarted = _currentCol == -1 && _currentRow == -1;

    if (notStarted){
           insertRow(0);
           _currentCol = 0;
           _currentRow = 0;

           setCellWidget(_currentRow, _currentCol, component);
           setCurrentCell(_currentRow, _currentCol);
           scrollToBottom();

           _currentCol++;
       }
       else {
           setCellWidget(_currentRow, _currentCol, component);
           const auto isEndOfLine = _currentCol == 2;
           if (isEndOfLine && !gameFinished) {
               setCurrentCell(_currentRow, _currentCol);
               _moveNumber++;
               insertRow(_currentRow+1);

               _currentRow++;
               _currentCol = 0;
               auto *numberComponent = buildMoveNumber();
               _widgetsItems.push_back(numberComponent);
               setCellWidget(_currentRow, _currentCol, numberComponent);
               scrollToBottom();
           }
           else {
               setCurrentCell(_currentRow, _currentCol);
               scrollToBottom();
           }

           _currentCol++;
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
    _cellToUpdate = nullptr;
    emit requestPositionOnBoard(new HistoryItem(QString(), _startPosition, LastMoveCoordinates(-1, -1, -1, -1)));
}

void loloof64::MovesHistory::gotoLastPosition()
{

}

void loloof64::MovesHistory::gotoPreviousPosition()
{

}

void loloof64::MovesHistory::gotoNextPosition()
{

}

void loloof64::MovesHistory::commitPositionRequest()
{
    if (_cellToUpdate == nullptr)
    {
        clearSelection();
        scrollToTop();
    }
    else {
        setCurrentCell(_cellToUpdate->row, _cellToUpdate->col);
    }
    clearPositionRequest();
}

void loloof64::MovesHistory::clearPositionRequest()
{
    _cellToUpdate = nullptr;
}
