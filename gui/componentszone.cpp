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
#include <QTimer>

loloof64::ComponentsZone::ComponentsZone(QWidget *parent) : QWidget(parent)
{
    _mainLayout = new QHBoxLayout(this);
    _mainLayout->setSpacing(20);
    _chessBoard = new ChessBoard(45, this);
    _movesHistory = new MovesHistoryFullComponent(this);
    _pgnDatabase = new PgnDatabase(false);

    _gameSelectionDialog = new GameSelectionDialog(this);

    _variantSelectionZone = new QScrollArea(this);
    _variantSelectionZoneLayout = new QVBoxLayout(_variantSelectionZone);
    _variantSelectionZoneLayout->setSpacing(10);
    _variantSelectionZoneWidget = new QFrame(this);
    _variantSelectionZoneWidget->setLayout(_variantSelectionZoneLayout);
    _variantSelectionZoneLabel = new QLabel(tr("Variant selection"), this);
    _variantMainButton = new QListWidget(_variantSelectionZoneWidget);
    _variantVariantsButtons = new QListWidget(_variantSelectionZoneWidget);
    _variantSelectionZoneLayout->addWidget(_variantSelectionZoneLabel);
    _variantSelectionZoneLayout->addWidget(_variantMainButton);
    _variantSelectionZoneLayout->addWidget(_variantVariantsButtons);
    _variantSelectionZone->setWidget(_variantSelectionZoneWidget);

    _mainLayout->addWidget(_chessBoard);
    _mainLayout->addWidget(_variantSelectionZone);
    _mainLayout->addWidget(_movesHistory);
    setLayout(_mainLayout);
    resize(800, 540);

    connect(_chessBoard, &loloof64::ChessBoard::moveDoneAsFan,
            [this](QString moveFan, QString newPositionFen, MoveCoordinates lastMove, bool gameFinished)
    {
        _movesHistory->addHistoryItem(new HistoryItem(moveFan, newPositionFen, lastMove), gameFinished);
        const auto noMoreMove = ! _currentGame.hasNextMove();
        if (noMoreMove){
            _chessBoard->stopGame();
            QMessageBox::information(this, tr("Congratulation"), tr("You found all the moves"));
        }
    });
    connect(_movesHistory->getMovesHistoryMainComponent(), &loloof64::MovesHistory::requestPositionOnBoard,
            [this](HistoryItem *item)
    {
       const auto validated = _chessBoard->setPosition(item);
       if (validated)
       {
           _movesHistory->commitHistoryNodeSelection();
       }
    });
    connect(_chessBoard, &loloof64::ChessBoard::externalTurn,
            [this](QString /*currentPosition*/)
    {
        makeComputerPlayNextMove();
    });
    connect(_chessBoard, &loloof64::ChessBoard::moveDoneAsSan,
            [this](QString moveSan, QString /*newPositionFen*/, MoveCoordinates moveCoordinates, bool /*gameFinished*/)
    {
        const auto stdMoveSan = moveSan.toStdString();
        char promotion = 0;
        const auto equalSignPos = stdMoveSan.find("=");
        if (equalSignPos != std::string::npos) {
            const auto promotionPart = stdMoveSan.substr(equalSignPos+1);
            promotion = promotionPart[0];
        }
        handleMoveVerification(moveCoordinates, promotion);
    });

    connect(_movesHistory->getButtonsZone(), &MovesHistoryButtons::requestFirstPosition,
            [this](){ _movesHistory->getMovesHistoryMainComponent()->gotoFirstPosition(); });
    connect(_movesHistory->getButtonsZone(), &MovesHistoryButtons::requestLastPosition,
            [this](){ _movesHistory->getMovesHistoryMainComponent()->gotoLastPosition(); });
    connect(_movesHistory->getButtonsZone(), &MovesHistoryButtons::requestPreviousPosition,
            [this](){ _movesHistory->getMovesHistoryMainComponent()->gotoPreviousPosition(); });
    connect(_movesHistory->getButtonsZone(), &MovesHistoryButtons::requestNextPosition,
            [this](){ _movesHistory->getMovesHistoryMainComponent()->gotoNextPosition(); });

    connect(_variantMainButton, &QListWidget::itemClicked, this, [this](QListWidgetItem * /*item*/)
    {
        auto nextMoveId = _currentGame.nextMove();

        const auto move = _currentGame.move(nextMoveId);
        _currentGame.findNextMove(move);

        const auto startFile = move.from() % 8;
        const auto startRank = move.from() / 8;
        const auto endFile = move.to() % 8;
        const auto endRank = move.to() / 8;

        clearVariants();

        if (move.isPromotion())
        {
            const auto promotion = move.promotedPiece();
            char promotionFen = promotionPieceToPromotionFen(promotion);
            QTimer::singleShot(600, [startFile, startRank, endFile, endRank, promotionFen, this](){
                _chessBoard->playMove(startFile, startRank, endFile, endRank, promotionFen);
            });
        }
        else {
            QTimer::singleShot(600, [startFile, startRank, endFile, endRank, this](){
                _chessBoard->playMove(startFile, startRank, endFile, endRank);
            });
        }
    });

    connect(_variantVariantsButtons, &QListWidget::itemClicked, this, [this](QListWidgetItem *item)
    {
        const auto index = _variantVariantsButtons->row(item);
        const auto moveId = _currentGame.variations()[index];
        const auto move = _currentGame.move(moveId);

        _currentGame.findNextMove(move);

        const auto startFile = move.from() % 8;
        const auto startRank = move.from() / 8;
        const auto endFile = move.to() % 8;
        const auto endRank = move.to() / 8;

        clearVariants();

        if (move.isPromotion())
        {
            const auto promotion = move.promotedPiece();
            char promotionFen = promotionPieceToPromotionFen(promotion);
            QTimer::singleShot(600, [startFile, startRank, endFile, endRank, promotionFen, this](){
                _chessBoard->playMove(startFile, startRank, endFile, endRank, promotionFen);
            });
        }
        else {
            QTimer::singleShot(600, [startFile, startRank, endFile, endRank, this](){
                _chessBoard->playMove(startFile, startRank, endFile, endRank);
            });
        }
    });
}

loloof64::ComponentsZone::~ComponentsZone()
{
    clearVariants();

    delete _variantVariantsButtons;
    delete _variantMainButton;
    delete _variantSelectionZoneLabel;
    delete _variantSelectionZoneLayout;
    delete _variantSelectionZoneWidget;
    delete _variantSelectionZone;

    _gameSelectionDialog->close();
    delete _gameSelectionDialog;

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

        _gameSelectionDialog->setPgnDatabase(_pgnDatabase);
        if (_gameSelectionDialog->exec() != QDialog::Accepted)
        {
            return;
        }

        auto selectedGameIndex = _gameSelectionDialog->getSelectedGameIndex();
        auto whitePlayerType = _gameSelectionDialog->getWhitePlayerType();
        auto blackPlayerType = _gameSelectionDialog->getBlackPlayerType();

        _chessBoard->setWhitePlayerType(whitePlayerType);
        _chessBoard->setBlackPlayerType(blackPlayerType);

        _pgnDatabase->loadGame(selectedGameIndex, _currentGame);
        _currentGame.moveToStart();

        // Starts game
        auto startPosition = _currentGame.board().toFen();

        _movesHistory->newGame(startPosition);
        _chessBoard->newGame(startPosition);

        const auto noMoreMove = ! _currentGame.hasNextMove();
        if (noMoreMove){
            _chessBoard->stopGame();
            QMessageBox::information(this, tr("Empty game"), tr("No move in this game"));
        }
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

void loloof64::ComponentsZone::handleMoveVerification(MoveCoordinates moveCoordinates, char promotion)
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
            promotionPiece = PieceType::Queen;
            break;
        case 'R':
        case 'r':
            promotionPiece = PieceType::Rook;
            break;
        case 'B':
        case 'b':
            promotionPiece = PieceType::Bishop;
            break;
        case 'N':
        case 'n':
            promotionPiece = PieceType::Knight;
            break;
        }

        const auto isAMatchingMove = _currentGame.findNextMove(
            fromSquare, toSquare, promotionPiece
        );

        if (! isAMatchingMove)
        {
            _chessBoard->stopGame();
            QTimer timer(this);
            timer.singleShot(500, this, [this](){
                showLoosingMessage();
            });
        }
    }
}

void loloof64::ComponentsZone::makeComputerPlayNextMove()
{
    if (!gameInProgress()) return;
    const auto whiteTurn = _chessBoard->isWhiteTurn();
    const auto isExternalTurn = (whiteTurn && _chessBoard->getWhitePlayerType() == PlayerType::EXTERNAL) ||
            (!whiteTurn && _chessBoard->getBlackPlayerType() == PlayerType::EXTERNAL);
    if (!isExternalTurn) return;


    if (_currentGame.variationCount() > 0)
    {
        const auto nextMoveId = _currentGame.nextMove();
        const auto nextMove = _currentGame.move(nextMoveId);

        const auto startFile = nextMove.from() % 8;
        const auto startRank = nextMove.from() / 8;
        const auto endFile = nextMove.to() % 8;
        const auto endRank = nextMove.to() / 8;

        char nextMovePromotionFen = 0;
        if (nextMove.isPromotion())
        {
            const auto promotion = nextMove.promotedPiece();
            nextMovePromotionFen = promotionPieceToPromotionFen(promotion);
        }

        const auto mainMoveFan = _chessBoard->getMoveFan(startFile, startRank, endFile, endRank, nextMovePromotionFen);
        _variantMainButton->addItem(mainMoveFan);

        const auto variationsIds = _currentGame.variations();
        for (const auto currentVariationId: variationsIds)
        {
            const auto variation = _currentGame.move(currentVariationId);

            const auto variationStartFile = variation.from() % 8;
            const auto variationStartRank = variation.from() / 8;
            const auto variationEndFile = variation.to() % 8;
            const auto variationEndRank = variation.to() / 8;

            char variationPromotionFen = 0;
            if (variation.isPromotion())
            {
                const auto promotion = variation.promotedPiece();
                variationPromotionFen = promotionPieceToPromotionFen(promotion);
            }

            const auto variationMoveFan = _chessBoard->getMoveFan(variationStartFile, variationStartRank, variationEndFile, variationEndRank, variationPromotionFen);
            _variantVariantsButtons->addItem(variationMoveFan);
        }

        return;
    }
    else
    {
        auto nextMoveId = _currentGame.nextMove();

        const auto move = _currentGame.move(nextMoveId);
        _currentGame.findNextMove(move);

        const auto startFile = move.from() % 8;
        const auto startRank = move.from() / 8;
        const auto endFile = move.to() % 8;
        const auto endRank = move.to() / 8;

        if (move.isPromotion())
        {
            const auto promotion = move.promotedPiece();
            char promotionFen = promotionPieceToPromotionFen(promotion);
            _chessBoard->playMove(startFile, startRank, endFile, endRank, promotionFen);
        }
        else {
            _chessBoard->playMove(startFile, startRank, endFile, endRank);
        }
    }
}

void loloof64::ComponentsZone::showLoosingMessage()
{
    QMessageBox::critical(this, tr("Lost game"), tr("You did not find one of the expected moves"));
}

char loloof64::ComponentsZone::promotionPieceToPromotionFen(Piece promotion) const
{
    char promotionFen = 0;

    switch (promotion) {
    case Piece::WhiteQueen: promotionFen = 'Q'; break;
    case Piece::BlackQueen: promotionFen = 'q'; break;
    case Piece::WhiteRook: promotionFen = 'R'; break;
    case Piece::BlackRook: promotionFen = 'r'; break;
    case Piece::WhiteBishop: promotionFen = 'B'; break;
    case Piece::BlackBishop: promotionFen = 'b'; break;
    case Piece::WhiteKnight: promotionFen = 'N'; break;
    case Piece::BlackKnight: promotionFen = 'n'; break;
    default: ;
    }

    return promotionFen;
}

void loloof64::ComponentsZone::clearVariants()
{
    _variantMainButton->clear();
    _variantVariantsButtons->clear();
}
