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
    _board->setWhitePlayerType(PlayerType::EXTERNAL);
    _board->setBlackPlayerType(PlayerType::EXTERNAL);

    connect(_goFirstButton, &QPushButton::clicked,
            [this]()
    {
       if (_pgnDatabase == nullptr) return;

       _selectedGameIndex = 0;
       loadGameStart();
    });

    connect(_goPreviousButton, &QPushButton::clicked, [this]()
    {
        if (_pgnDatabase == nullptr) return;
        if (_selectedGameIndex == 0) return;

        _selectedGameIndex--;
        loadGameStart();
    });

    connect(_goNextButton, &QPushButton::clicked, [this]()
    {
        if (_pgnDatabase == nullptr) return;
        if (_selectedGameIndex >= _pgnDatabase->count() - 1) return;

        _selectedGameIndex++;
        loadGameStart();
    });

    connect(_goLastButton, &QPushButton::clicked, [this]()
    {
        if (_pgnDatabase == nullptr) return;

        _selectedGameIndex = _pgnDatabase->count() - 1;
        loadGameStart();
    });

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

void loloof64::GameSelectionMainZone::setPgnDatabase(PgnDatabase *database)
{
    _pgnDatabase = database;

    if (_pgnDatabase != nullptr)
    {
        _selectedGameIndex = 0;
        loadGameStart();

        emit gameIndexChanged(_selectedGameIndex);
    }
}

void loloof64::GameSelectionMainZone::loadGameStart()
{
    if (_pgnDatabase == nullptr) return;

    _pgnDatabase->loadGame(_selectedGameIndex, _currentBaseGame);
    _currentBaseGame.moveToStart();

    auto gameStartPosition = _currentBaseGame.toFen();
    _board->setPosition(new HistoryItem(QString(), gameStartPosition, MoveCoordinates(-1, -1, -1, -1)));

    auto whitePlayer = _currentBaseGame.tag("White");
    auto blackPlayer = _currentBaseGame.tag("Black");

    auto date = _currentBaseGame.tag("Date");
    auto event = _currentBaseGame.tag("Event");
    auto site = _currentBaseGame.tag("Site");

    emit gameIndexChanged(_selectedGameIndex);
    emit whitePlayerChanged(whitePlayer);
    emit blackPlayerChanged(blackPlayer);
    emit gameDateChanged(date);
    emit gameEventChanged(event);
    emit gameSiteChanged(site);
}

quint64 loloof64::GameSelectionMainZone::getSelectedGameIndex() const
{
    return _selectedGameIndex;
}
