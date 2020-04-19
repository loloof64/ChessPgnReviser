#include "componentszone.h"
#include "./adapters/thcposition.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QDataStream>

loloof64::ComponentsZone::ComponentsZone(QWidget *parent) : QWidget(parent)
{
    _mainLayout = new QHBoxLayout(this);
    _mainLayout->setSpacing(20);
    _chessBoard = new ChessBoard(60, this);
    _movesHistory = new MovesHistory(this);
    _pgnDatabase = new PgnDatabase(false);

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
            [this](QString moveSan, QString /*newPositionFen*/, LastMoveCoordinates moveCoordinates, bool /*gameFinished*/)
    {
        const auto stdMoveSan = moveSan.toStdString();
        auto promotion = 0;
        const auto equalSign = stdMoveSan.find_last_of("=");
        if (equalSign > -1) {
            const auto promotionPart = stdMoveSan.substr(equalSign);
            promotion = promotionPart[0];
        }
        handleMoveVerification(moveCoordinates, promotion);
    });
}

loloof64::ComponentsZone::~ComponentsZone()
{
    if (_pgnDatabase != nullptr)
    {
        _pgnDatabase->close();
        delete _pgnDatabase;
        _pgnDatabase = nullptr;
    }
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
        if (_pgnDatabase != nullptr)
        {
            _pgnDatabase->close();
            delete _pgnDatabase;
            _pgnDatabase = nullptr;
        }
        _pgnDatabase = new PgnDatabase(false);
        _pgnDatabase->open(fileName, true);

        auto selectedGameIndex = 0;

        _pgnDatabase->loadGame(selectedGameIndex, _currentGame);
        _currentGame.moveToStart();

        // Starts game
        const auto moveNumber = _currentGame.moveNumber(0);
        auto startPosition = _currentGame.board().toFen();

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
    if (_pgnDatabase != nullptr)
    {
        delete _pgnDatabase;
        _pgnDatabase->close();
        _pgnDatabase = nullptr;
    }
}

void loloof64::ComponentsZone::handleMoveVerification(LastMoveCoordinates moveCoordinates, char promotion)
{
    const auto whiteTurnBeforeMove = ! _chessBoard->isWhiteTurn();
    const auto externalPlayerTurn = (whiteTurnBeforeMove && (_chessBoard->getWhitePlayerType() == PlayerType::EXTERNAL)) ||
            (!whiteTurnBeforeMove && (_chessBoard->getBlackPlayerType() == PlayerType::EXTERNAL));

    if (externalPlayerTurn) {
        return;
    }
    else {
        auto promotionPiece = PieceType::None;
        const auto fromSquare = SquareFromRankAndFile((unsigned char) moveCoordinates.startRank, (unsigned char) moveCoordinates.startFile);
        const auto toSquare = SquareFromRankAndFile((unsigned char) moveCoordinates.endRank, (unsigned char) moveCoordinates.endFile);
        switch (promotion) {
        case 'Q':
        case 'q':
            promotion = PieceType::Queen;
            break;
        case 'R':
        case 'r':
            promotion = PieceType::Rook;
            break;
        case 'B':
        case 'b':
            promotion = PieceType::Bishop;
            break;
        case 'N':
        case 'n':
            promotion = PieceType::Knight;
            break;
        }

        const auto isAMatchingMove = _currentGame.findNextMove(
            fromSquare, toSquare, promotionPiece
        );

        if (isAMatchingMove)
        {

        }
        else {
            QMessageBox::critical(this, tr("Lost game"), tr("You did not find one of the expected moves"));
            _chessBoard->stopGame();
        }
    }
}
