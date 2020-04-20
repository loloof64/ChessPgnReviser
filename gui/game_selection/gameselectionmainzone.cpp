#include "gameselectionmainzone.h"

loloof64::GameSelectionMainZone::GameSelectionMainZone(QWidget *parent) : QWidget(parent)
{
    _layout = new QHBoxLayout();
    _layout->setSpacing(10);

    _goFirstButton = new QPushButton(QIcon(QPixmap(":/icons/previous.svg")), QString(), this);
    _goFirstButton->setToolTip(QString(tr("Goto first")));

    _goPreviousButton = new QPushButton(QIcon(QPixmap(":/icons/left.svg")), QString(), this);
    _goPreviousButton->setToolTip(QString(tr("Goto previous")));

    _goNextButton = new QPushButton(QIcon(QPixmap(":/icons/right.svg")), QString(), this);
    _goNextButton->setToolTip(QString(tr("Goto next")));

    _goLastButton = new QPushButton(QIcon(QPixmap(":/icons/next.svg")), QString(), this);
    _goLastButton->setToolTip(QString(tr("Goto last")));

    _board = new ChessBoard(20);

    _layout->addWidget(_goFirstButton);
    _layout->addWidget(_goPreviousButton);
    _layout->addWidget(_board);
    _layout->addWidget(_goNextButton);
    _layout->addWidget(_goLastButton);

    setLayout(_layout);
}

loloof64::GameSelectionMainZone::~GameSelectionMainZone()
{
    delete _board;
    delete _goLastButton;
    delete _goNextButton;
    delete _goPreviousButton;
    delete _goFirstButton;
    delete _layout;
}
