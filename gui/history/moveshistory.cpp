#include "moveshistory.h"
#include <QLabel>
#include <QHeaderView>
#include <string>

loloof64::MovesHistory::MovesHistory(QWidget *parent) : QTableWidget(parent)
{
    setColumnCount(3);
    setHorizontalHeaderLabels(QStringList(QList<QString>{tr("Move number"), tr("White"), tr("Black")}));
    verticalHeader()->hide();
}

loloof64::MovesHistory::~MovesHistory()
{
    clearMoves();
}

void loloof64::MovesHistory::newGame(int moveNumber)
{
    clearMoves();


    addComponent(buildMoveNumber(moveNumber));
}

void loloof64::MovesHistory::addMoveFan(QString moveFan)
{
    // add move fan as a qpushbutton
}

void loloof64::MovesHistory::clearMoves()
{
    setRowCount(0);
    for (auto it = items.rbegin(); it != items.rend(); ++it )
    {
        if (*it != nullptr) {
            delete *it;
            *it = nullptr;
        }
    }
    currentRow = -1;
    currentCol = -1;
}

void loloof64::MovesHistory::addComponent(QWidget *component)
{
    items.push_back(component);
    const auto notStarted = currentCol == -1 && currentRow == -1;
    if (notStarted){
        insertRow(0);
        currentCol = 0;
        currentRow = 0;

        setCellWidget(currentRow, currentCol, component);
    }
    else {
        setCellWidget(currentRow, currentCol, component);
        const auto isEndOfLine = currentCol == 2;
        if (isEndOfLine) {
            insertRow(currentRow+1);
            currentRow++;
            currentCol = 0;
        }
        else {
            currentCol++;
        }
    }
}

QLabel* loloof64::MovesHistory::buildMoveNumber(int moveNumber)
{
    auto *numberComponent = new QLabel{QString(std::to_string(moveNumber).c_str()), this};
    numberComponent->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    numberComponent->setMargin(5);

    return numberComponent;
}
