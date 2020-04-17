#include "componentszone.h"
#include "./adapters/thcposition.h"
#include <fstream>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QDataStream>

#include <iostream>

loloof64::ComponentsZone::ComponentsZone(QWidget *parent) : QWidget(parent), _pgnDatabase(false)
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
            [this](QString moveFan, QString newPositionFen, LastMoveCoordinates lastMove, bool gameFinished)
    {
        _movesHistory->addHistoryItem(new HistoryItem(moveFan, newPositionFen, lastMove), gameFinished);
    });
    connect(_movesHistory, &loloof64::MovesHistory::requestPositionOnBoard,
            [this](HistoryItem *item)
    {
       _chessBoard->setPosition(item);
    });
    connect(_chessBoard, &loloof64::ChessBoard::externalTurn,
            [this](QString /*currentPosition*/)
    {

    });
    connect(_chessBoard, &loloof64::ChessBoard::moveDoneAsSan,
            [this](QString moveFan, QString /*newPositionFen*/, LastMoveCoordinates /*lastMove*/, bool /*gameFinished*/)
    {
        handleMoveVerification(moveFan);
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
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select the game pgn"), "",
                                                   tr("Chess game (*.pgn)"));


    if (fileName.isEmpty())
            return;

    try {
        _pgnDatabase.open(fileName, true);
        _pgnDatabase.loadGame(0, _currentGame);

        const auto moveNumber = _currentGame.moveNumber();
        const auto startPosition = _currentGame.toFen();

        // Starts game

        _movesHistory->newGame(moveNumber);

        _chessBoard->setWhitePlayerType(PlayerType::HUMAN);
        _chessBoard->setBlackPlayerType(PlayerType::EXTERNAL);
        _chessBoard->newGame(startPosition);
    }
    catch (loloof64::IllegalPositionException const &e)
    {
        QMessageBox::information(this, tr("Unable to open file"),
                        tr("Wrong game data"));
                    return;
    }
    catch (std::exception const &e)
    {
        QMessageBox::information(this, tr("Unable to open file"),
                        e.what());
                    return;
    }
}

void loloof64::ComponentsZone::stopGame()
{
    _chessBoard->stopGame();
}

void loloof64::ComponentsZone::handleMoveVerification(QString moveSan)
{
    const auto whiteTurn = _chessBoard->isWhiteTurn();
    const auto externalPlayerTurn = (whiteTurn && (_chessBoard->getWhitePlayerType() == PlayerType::EXTERNAL)) ||
            (!whiteTurn && (_chessBoard->getBlackPlayerType() == PlayerType::EXTERNAL));
    if (externalPlayerTurn) {
        return;
    }
    else {

    }
}
