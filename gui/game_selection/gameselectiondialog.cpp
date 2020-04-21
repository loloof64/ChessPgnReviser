#include "gameselectiondialog.h"

loloof64::GameSelectionDialog::GameSelectionDialog(QWidget *parent) : QDialog(parent)
{
    _layout = new QVBoxLayout();
    _layout->setSpacing(20);

    _gameIndexLabel = new QLabel();
    _playersLabel = new QLabel();
    _eventLabel = new QLabel();

    _mainZone = new GameSelectionMainZone(this);

    _whitePlayerSelectionLine = new QFrame(this);
    _whitePlayerSelectionLineLayout = new QHBoxLayout();
    _whitePlayerSelectionLineLayout->setSpacing(5);
    _whitePlayerSelectionLabel = new QLabel(tr("White player"), _whitePlayerSelectionLine);
    _whitePlayerSelectionCombo = new QComboBox(_whitePlayerSelectionLine);
    _whitePlayerSelectionLineLayout->addWidget(_whitePlayerSelectionLabel);
    _whitePlayerSelectionLineLayout->addWidget(_whitePlayerSelectionCombo);
    _whitePlayerSelectionLine->setLayout(_whitePlayerSelectionLineLayout);
    _whitePlayerSelectionCombo->addItem(QString(tr("Human")));
    _whitePlayerSelectionCombo->addItem(QString(tr("Computer")));

    _blackPlayerSelectionLine = new QFrame(this);
    _blackPlayerSelectionLineLayout = new QHBoxLayout();
    _blackPlayerSelectionLineLayout->setSpacing(5);
    _blackPlayerSelectionLabel = new QLabel(tr("Black player"), _blackPlayerSelectionLine);
    _blackPlayerSelectionCombo = new QComboBox(_blackPlayerSelectionLine);
    _blackPlayerSelectionLineLayout->addWidget(_blackPlayerSelectionLabel);
    _blackPlayerSelectionLineLayout->addWidget(_blackPlayerSelectionCombo);
    _blackPlayerSelectionLine->setLayout(_blackPlayerSelectionLineLayout);
    _blackPlayerSelectionCombo->addItem(QString(tr("Human")));
    _blackPlayerSelectionCombo->addItem(QString(tr("Computer")));

    _validateButton = new QPushButton(tr("Validate"));

    _layout->addWidget(_gameIndexLabel);
    _layout->addWidget(_mainZone);
    _layout->addWidget(_playersLabel);
    _layout->addWidget(_eventLabel);
    _layout->addWidget(_whitePlayerSelectionLine);
    _layout->addWidget(_blackPlayerSelectionLine);
    _layout->addWidget(_validateButton);

    setLayout(_layout);

    setModal(true);
}

loloof64::GameSelectionDialog::~GameSelectionDialog()
{
    delete _validateButton;

    delete _blackPlayerSelectionCombo;
    delete _blackPlayerSelectionLabel;
    delete _blackPlayerSelectionLineLayout;
    delete _blackPlayerSelectionLine;

    delete _whitePlayerSelectionCombo;
    delete _whitePlayerSelectionLabel;
    delete _whitePlayerSelectionLineLayout;
    delete _whitePlayerSelectionLine;

    delete _mainZone;

    delete _eventLabel;
    delete _playersLabel;
    delete _gameIndexLabel;
    delete _layout;
}

void loloof64::GameSelectionDialog::setPgnDatabase(PgnDatabase *database)
{
    _mainZone->setPgnDatabase(database);
}
