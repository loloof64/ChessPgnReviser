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
}

loloof64::MovesHistory::~MovesHistory()
{
    clearMoves();
}

void loloof64::MovesHistory::newGame(int moveNumber)
{
    clearMoves();
    this->moveNumber = moveNumber;
    addComponent(buildMoveNumber());
}

void loloof64::MovesHistory::addMoveFan(QString moveFan)
{
    auto moveButton = new QPushButton(moveFan, this);
    moveButton->setFlat(true);
    moveButton->setStyleSheet("text-align: right; margin: 5px; font-size: 18px;");
    addComponent(moveButton);
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
        setCurrentCell(currentRow, currentCol);

        currentCol++;
    }
    else {
        setCellWidget(currentRow, currentCol, component);
        const auto isEndOfLine = currentCol == 2;
        if (isEndOfLine) {
            moveNumber++;
            insertRow(currentRow+1);

            currentRow++;
            currentCol = 0;
            auto *numberComponent = buildMoveNumber();
            items.push_back(component);
            setCellWidget(currentRow, currentCol, numberComponent);
        }
        setCurrentCell(currentRow, currentCol);
        scrollToBottom();

        currentCol++;
    }
}

QLabel* loloof64::MovesHistory::buildMoveNumber()
{
    auto *numberComponent = new QLabel{QString(std::to_string(moveNumber).c_str()), this};
    numberComponent->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    numberComponent->setMargin(5);
    auto font = QFont();
    font.setPointSize(18);
    numberComponent->setFont(QFont());

    return numberComponent;
}
