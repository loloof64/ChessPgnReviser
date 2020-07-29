#include "moveshistorybuttons.h"

loloof64::MovesHistoryButtons::MovesHistoryButtons(QWidget *parent) : QWidget(parent)
{
    _mainLayout = new QHBoxLayout(this);

    _gotoStartButton = new QPushButton(QIcon(QPixmap(":/icons/previous.svg")), QString(), this);
    _gotoStartButton->setToolTip(tr("Goto start"));

    _gotoPreviousButton = new QPushButton(QIcon(QPixmap(":/icons/left.svg")), QString(), this);
    _gotoPreviousButton->setToolTip(tr("Goto previous"));

    _gotoNextButton = new QPushButton(QIcon(QPixmap(":/icons/right.svg")), QString(), this);
    _gotoNextButton->setToolTip(tr("Goto next"));

    _gotoEndButton = new QPushButton(QIcon(QPixmap(":/icons/next.svg")), QString(), this);
    _gotoEndButton->setToolTip(tr("Goto end"));

    _mainLayout->addWidget(_gotoStartButton);
    _mainLayout->addWidget(_gotoPreviousButton);
    _mainLayout->addWidget(_gotoNextButton);
    _mainLayout->addWidget(_gotoEndButton);

    connect(_gotoStartButton, &QPushButton::clicked, this, [this](){ emit requestFirstPosition(); });
    connect(_gotoEndButton, &QPushButton::clicked, this, [this](){ emit requestLastPosition(); });
    connect(_gotoPreviousButton, &QPushButton::clicked, this, [this](){ emit requestPreviousPosition(); });
    connect(_gotoNextButton, &QPushButton::clicked, this, [this](){ emit requestNextPosition(); });

    setLayout(_mainLayout);
}

loloof64::MovesHistoryButtons::~MovesHistoryButtons()
{
    delete _mainLayout;
}
