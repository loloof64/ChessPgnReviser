#include "componentszone.h"

loloof64::ComponentsZone::ComponentsZone(QWidget *parent) : QWidget(parent)
{
    _mainLayout = new QHBoxLayout(this);
    _mainLayout->setSpacing(20);
    _chessBoard = new ChessBoard(60, this);
    _movesHistory = new MovesHistory(this);

    _mainLayout->addWidget(_chessBoard);
    _mainLayout->addWidget(_movesHistory);
    setLayout(_mainLayout);
    resize(800, 540);

    connect(_chessBoard, &loloof64::ChessBoard::moveDoneAsFan,
            [this](QString moveFan){
        _movesHistory->addMoveFan(moveFan);
    });
}

loloof64::ComponentsZone::~ComponentsZone()
{
    delete _movesHistory;
    delete _chessBoard;
    delete _mainLayout;
}

void loloof64::ComponentsZone::reverseBoard()
{
    _chessBoard->reverse();
}

void loloof64::ComponentsZone::newGame()
{
    _movesHistory->newGame();
    _chessBoard->newGame();
}

void loloof64::ComponentsZone::stopGame()
{
    _chessBoard->stopGame();
}
