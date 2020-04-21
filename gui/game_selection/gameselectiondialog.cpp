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

    _layout->setAlignment(_gameIndexLabel, Qt::AlignHCenter);
    _layout->setAlignment(_mainZone, Qt::AlignHCenter);
    _layout->setAlignment(_playersLabel, Qt::AlignHCenter);
    _layout->setAlignment(_eventLabel, Qt::AlignHCenter);
    _layout->setAlignment(_whitePlayerSelectionLine, Qt::AlignHCenter);
    _layout->setAlignment(_blackPlayerSelectionLine, Qt::AlignHCenter);
    _layout->setAlignment(_validateButton, Qt::AlignHCenter);

    setLayout(_layout);

    connect(_mainZone, &GameSelectionMainZone::gameIndexChanged, this, [this](quint64 selectedIndex)
    {
        _gameIndexLabel->setText(QString("%1 / %2").arg(selectedIndex + 1).arg(_gamesCount));
    });

    connect(_mainZone, &GameSelectionMainZone::whitePlayerChanged, this, [this](QString name)
    {
        _whitePlayerName = name;
        auto whiteName = _whitePlayerName;
        if (whiteName.isEmpty()) whiteName = QString(tr("Unknown"));

        auto blackName = _blackPlayerName;
        if (blackName.isEmpty()) blackName = QString(tr("Unknown"));

        _playersLabel->setText(QString("%1 / %2").arg(whiteName).arg(blackName));
    });

    connect(_mainZone, &GameSelectionMainZone::blackPlayerChanged, this, [this](QString name)
    {
        _blackPlayerName = name;
        auto whiteName = _whitePlayerName;
        if (whiteName.isEmpty()) whiteName = QString(tr("Unknown"));

        auto blackName = _blackPlayerName;
        if (blackName.isEmpty()) blackName = QString(tr("Unknown"));

        _playersLabel->setText(QString("%1 / %2").arg(whiteName).arg(blackName));
    });

    connect(_mainZone, &GameSelectionMainZone::gameDateChanged, this, [this](QString date)
    {
        _eventDate = date;
        auto newDate = date;
        if (newDate.isEmpty()) newDate = QString(tr("Unknown"));

        auto newEventName = _eventName;
        if (newEventName.isEmpty()) newEventName = QString(tr("Unknown"));

        auto newSite = _eventSite;
        if (newSite.isEmpty()) newSite = QString(tr("Unknown"));

        _eventLabel->setText(QString("%1 - %2 (%3)").arg(newEventName).arg(newSite).arg(newDate));
    });

    connect(_mainZone, &GameSelectionMainZone::gameEventChanged, this, [this](QString event)
    {
        _eventName = event;
        auto newDate = _eventDate;
        if (newDate.isEmpty()) newDate = QString(tr("Unknown"));

        auto newEventName = _eventName;
        if (newEventName.isEmpty()) newEventName = QString(tr("Unknown"));

        auto newSite = _eventSite;
        if (newSite.isEmpty()) newSite = QString(tr("Unknown"));

        _eventLabel->setText(QString("%1 - %2 (%3)").arg(newEventName).arg(newSite).arg(newDate));
    });

    connect(_mainZone, &GameSelectionMainZone::gameSiteChanged, this, [this](QString site)
    {
        _eventSite = site;
        auto newDate = _eventDate;
        if (newDate.isEmpty()) newDate = QString(tr("Unknown"));

        auto newEventName = _eventName;
        if (newEventName.isEmpty()) newEventName = QString(tr("Unknown"));

        auto newSite = _eventSite;
        if (newSite.isEmpty()) newSite = QString(tr("Unknown"));

        _eventLabel->setText(QString("%1 - %2 (%3)").arg(newEventName).arg(newSite).arg(newDate));
    });

    connect(_whitePlayerSelectionCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index)
    {
        if (index == 1)
        {
            _whitePlayerType = PlayerType::EXTERNAL;
        }
        else {
            _whitePlayerType = PlayerType::HUMAN;
        }
    });

    connect(_blackPlayerSelectionCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index)
    {
        if (index == 1)
        {
            _blackPlayerType = PlayerType::EXTERNAL;
        }
        else {
            _blackPlayerType = PlayerType::HUMAN;
        }
    });

    connect(_validateButton, &QPushButton::clicked, this, [this]()
    {
        accept();
    });

    _whitePlayerType = PlayerType::HUMAN;
    _blackPlayerType = PlayerType::HUMAN;

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
    _gamesCount = database->count();

    _gameIndexLabel->setText(QString("%1 / %2").arg(1).arg(_gamesCount));
}

quint64 loloof64::GameSelectionDialog::getSelectedGameIndex() const
{
    return _mainZone->getSelectedGameIndex();
}

loloof64::PlayerType loloof64::GameSelectionDialog::getWhitePlayerType() const
{
    return _whitePlayerType;
}

loloof64::PlayerType loloof64::GameSelectionDialog::getBlackPlayerType() const
{
    return _blackPlayerType;
}
