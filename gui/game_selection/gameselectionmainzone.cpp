#include "gameselectionmainzone.h"

loloof64::GameSelectionMainZone::GameSelectionMainZone(QWidget *parent) : QWidget(parent)
{
    _overallLayout = new QVBoxLayout(this);

    _gameTextSelection = new QLineEdit(this);
    _gameTextSelection->setMaximumWidth(50);

    _mainZone = new QFrame(this);
    _layout = new QHBoxLayout();
    _layout->setSpacing(10);
    _mainZone->setLayout(_layout);

    _goFirstButton = new QPushButton(QIcon(QPixmap(":/icons/previous.svg")), QString(), _mainZone);
    _goFirstButton->setToolTip(QString(tr("Goto first")));

    _goPreviousButton = new QPushButton(QIcon(QPixmap(":/icons/left.svg")), QString(), _mainZone);
    _goPreviousButton->setToolTip(QString(tr("Goto previous")));

    _goNextButton = new QPushButton(QIcon(QPixmap(":/icons/right.svg")), QString(), _mainZone);
    _goNextButton->setToolTip(QString(tr("Goto next")));

    _goLastButton = new QPushButton(QIcon(QPixmap(":/icons/next.svg")), QString(), _mainZone);
    _goLastButton->setToolTip(QString(tr("Goto last")));

    _board = new ChessBoard(20, _mainZone);
    _board->setWhitePlayerType(PlayerType::EXTERNAL);
    _board->setBlackPlayerType(PlayerType::EXTERNAL);

    connect(_goFirstButton, &QPushButton::clicked,
            [this]()
    {
       if (_pgnDatabase == nullptr) return;

       _selectedGameIndex = 0;
       _gameTextSelection->setText(QString("%1").arg(_selectedGameIndex+1));
       loadGameStart();
    });

    connect(_goPreviousButton, &QPushButton::clicked, [this]()
    {
        if (_pgnDatabase == nullptr) return;
        if (_selectedGameIndex == 0) return;

        _selectedGameIndex--;
        _gameTextSelection->setText(QString("%1").arg(_selectedGameIndex+1));
        loadGameStart();
    });

    connect(_goNextButton, &QPushButton::clicked, [this]()
    {
        if (_pgnDatabase == nullptr) return;
        if (_selectedGameIndex >= _pgnDatabase->count() - 1) return;

        _selectedGameIndex++;
        _gameTextSelection->setText(QString("%1").arg(_selectedGameIndex+1));
        loadGameStart();
    });

    connect(_goLastButton, &QPushButton::clicked, [this]()
    {
        if (_pgnDatabase == nullptr) return;

        _selectedGameIndex = _pgnDatabase->count() - 1;
        _gameTextSelection->setText(QString("%1").arg(_selectedGameIndex+1));
        loadGameStart();
    });

    connect(_gameTextSelection, &QLineEdit::textChanged, this, [this](QString)
    {
        const auto valueText = _gameTextSelection->text();
        if (valueText.isEmpty()) return;

        const auto valuetoSet = static_cast<quint64>(std::stoi(valueText.toStdString().c_str())) -1;
        const auto inBounds = valuetoSet >= 0 && valuetoSet < _pgnDatabase->count();
        if (inBounds)
        {
            _selectedGameIndex = valuetoSet;
            loadGameStart();
        }
    });

    _layout->addWidget(_goFirstButton);
    _layout->addWidget(_goPreviousButton);
    _layout->addWidget(_board);
    _layout->addWidget(_goNextButton);
    _layout->addWidget(_goLastButton);

    _overallLayout->addWidget(_gameTextSelection);
    _overallLayout->addWidget(_mainZone);
    _overallLayout->setAlignment(_gameTextSelection, Qt::AlignHCenter);
    _overallLayout->setAlignment(_mainZone, Qt::AlignHCenter);

    setLayout(_overallLayout);
}

loloof64::GameSelectionMainZone::~GameSelectionMainZone()
{
    delete _board;
    delete _goLastButton;
    delete _goNextButton;
    delete _goPreviousButton;
    delete _goFirstButton;
    delete _layout;
    delete _mainZone;

    if (_gameTextValidator != nullptr) delete _gameTextValidator;
    delete _gameTextSelection;
    delete _overallLayout;
}

void loloof64::GameSelectionMainZone::setPgnDatabase(PgnDatabase *database)
{
    _pgnDatabase = database;

    if (_pgnDatabase != nullptr)
    {
        _gameTextValidator = new QIntValidator(1, _pgnDatabase->count(), this);
        _gameTextSelection->setValidator(_gameTextValidator);

        _selectedGameIndex = 0;
        _gameTextSelection->setText(QString("%1").arg(_selectedGameIndex+1));
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
    _board->setPosition(HistoryItem(QString(), gameStartPosition, MoveCoordinates(-1, -1, -1, -1)));

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
