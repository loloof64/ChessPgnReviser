#include "moveshistory.h"
#include <QLabel>
#include <QHeaderView>
#include <QPushButton>
#include <string>

loloof64::MovesHistory::MovesHistory(QWidget *parent) : QTableWidget(parent)
{
    setColumnCount(2);
    setHorizontalHeaderLabels(QStringList(QList<QString>{tr("White"), tr("Black")}));
    verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader()->setDefaultSectionSize(36);
}

loloof64::MovesHistory::~MovesHistory()
{
    clearMoves();
}

void loloof64::MovesHistory::newGame(int moveNumber)
{
    clearMoves();
    insertRow(0);
    this->_moveNumber = moveNumber;
    auto moveNumberItem = QTableWidgetItem(QString{std::to_string(moveNumber).c_str()});
    setVerticalHeaderItem(_currentRow, &moveNumberItem);
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

    _currentRow = 0;
    _currentCol = 0;
}

void loloof64::MovesHistory::addComponent(QWidget *component, bool gameFinished)
{
    _widgetsItems.push_back(component);

    setCellWidget(_currentRow, _currentCol, component);
    setCurrentCell(_currentRow, _currentCol);
    const auto isEndOfLine = _currentCol == 1;
    if (isEndOfLine && !gameFinished) {
        _moveNumber++;
        insertRow(_currentRow+1);
        _currentRow++;
        _currentCol = 0;
    }
    else {
        _currentCol++;
    }

    scrollToBottom();
}
