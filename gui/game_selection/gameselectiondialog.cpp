#include "gameselectiondialog.h"

loloof64::GameSelectionDialog::GameSelectionDialog(QWidget *parent) : QDialog(parent)
{
    _layout = new QVBoxLayout();
    _layout->setSpacing(20);

    _gameIndexLabel = new QLabel();
    _playersLabel = new QLabel();
    _eventLabel = new QLabel();

    _mainZone = new GameSelectionMainZone(this);

    _layout->addWidget(_gameIndexLabel);
    _layout->addWidget(_mainZone);
    _layout->addWidget(_playersLabel);
    _layout->addWidget(_eventLabel);

    setLayout(_layout);

    setModal(true);
}

loloof64::GameSelectionDialog::~GameSelectionDialog()
{
    delete _eventLabel;
    delete _playersLabel;
    delete _gameIndexLabel;
    delete _layout;
}
