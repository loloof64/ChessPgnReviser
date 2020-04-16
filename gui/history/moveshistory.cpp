#include "moveshistory.h"

loloof64::MovesHistory::MovesHistory(QWidget *parent) : QTableWidget(parent)
{
    setColumnCount(3);
    setHorizontalHeaderLabels(QStringList(QList<QString>{tr("Move number"), tr("White"), tr("Black")}));
}

loloof64::MovesHistory::~MovesHistory()
{

}
