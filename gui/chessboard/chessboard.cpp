#include "chessboard.h"
#include "promotiondialog.h"
#include "../../core/adapters/thcposition.h"
#include "../../core/IPosition.h"
#include <QPainter>
#include <QVector>
#include <QString>
#include <QSvgRenderer>
#include <QMessageBox>
#include <cmath>
#include <cctype>

using namespace loloof64;

ChessBoard::ChessBoard(int cellsSize, QWidget* parent) : QWidget(parent), _cellsSize(cellsSize)
{
    setMinimumSize(9*cellsSize, 9*cellsSize);
    setMaximumSize(9*cellsSize, 9*cellsSize);
    _relatedPosition = new ThcPosition("8/8/8/8/8/8/8/8 w - - 0 1");
    _dndData = nullptr;
    _gameFinishedStatus = GameFinishedStatus::STOPPED;
    _lastMoveCoordinates = nullptr;
    _reversed = false;
    auto wholeSize = 9 * cellsSize;
    setFixedSize(wholeSize, wholeSize);
}

ChessBoard::~ChessBoard()
{
    if (_lastMoveCoordinates != nullptr) delete _lastMoveCoordinates;
    if (_dndData != nullptr) delete _dndData;
    delete _relatedPosition;
}

void ChessBoard::reverse()
{
    _reversed = ! _reversed;
    repaint();
}

void ChessBoard::newGame(QString startPosition)
{
    if (_lastMoveCoordinates != nullptr)
    {
        delete _lastMoveCoordinates;
        _lastMoveCoordinates = nullptr;
    }
    _relatedPosition = new ThcPosition(startPosition.toStdString());
    _gameFinishedStatus = GameFinishedStatus::NOT_FINISHED;
    repaint();

    emitExternalPlayerTurnIfNecessary();
}

void ChessBoard::stopGame()
{
    _gameFinishedStatus = GameFinishedStatus::STOPPED;
    if (_dndData != nullptr) {
        delete _dndData;
        _dndData = nullptr;
    }

    repaint();

    emit gameEnded();
}

void ChessBoard::paintEvent(QPaintEvent * /* event */)
{
    const auto wholeSize = 9 * _cellsSize;
    const auto colsIndexes = QVector<int>{0,1,2,3,4,5,6,7};
    const auto rowsIndexes = QVector<int>{0,1,2,3,4,5,6,7};

    const auto backgroundColor = QColor(108, 93, 167);
    const auto whiteCellsColor = QColor(255, 206, 158);
    const auto blackCellsColor = QColor(209, 139, 71);
    const auto dndCrossCellColor = QColor(200, 115, 207);
    const auto dndStartCellColor = Qt::red;
    const auto dndEndCellColor = Qt::green;
    const auto lastMoveArrowColor = QColor(0, 0, 255, 200);

    QPainter painter(this);

    // painting background
    painter.fillRect(0, 0, wholeSize, wholeSize, backgroundColor);

    // painting cells
    for (auto row: rowsIndexes)
    {
        for (auto col: colsIndexes)
        {
            const auto file = _reversed ? 7-col : col;
            const auto rank = _reversed ? row : 7-row;

            // draw cell
            const auto isWhiteCell = (row+col) %2 == 0;
            const auto x = int(floor(_cellsSize * (0.5 + col)));
            const auto y = int(floor(_cellsSize * (0.5 + row)));
            auto cellColor = isWhiteCell ? whiteCellsColor : blackCellsColor;

           if (_dndData != nullptr && _dndData->pointerInBounds)
           {
               const auto isACrossDndCell = (file == _dndData->endFile) || (rank == _dndData->endRank);

               const auto isDndStartCell = (file == _dndData->startFile) && (rank == _dndData->startRank);


               const auto isDndEndCell = (file == _dndData->endFile) && (rank == _dndData->endRank);

               if (isACrossDndCell) cellColor = dndCrossCellColor;
               if (isDndStartCell) cellColor = dndStartCellColor;
               if (isDndEndCell) cellColor = dndEndCellColor;

           }

            painter.fillRect(x, y, _cellsSize, _cellsSize, cellColor);

            // draw piece
            const auto pieceValue = _relatedPosition->getPieceFenAt(file, rank);

            const auto notAnEmptyPiece = QVector<char>{
                'P', 'N', 'B', 'R', 'Q', 'K',
                'p', 'n', 'b', 'r', 'q', 'k'
            }.contains(pieceValue);
            const auto isTheMovedPiece = _dndData != nullptr && (file == _dndData->startFile) && (rank == _dndData->startRank);

            if (notAnEmptyPiece && !isTheMovedPiece)
            {
                auto resourceName = QString(":/chess_vectors/");
                resourceName += IPosition::pieceFenToPieceImageReference(pieceValue);
                QSvgRenderer pieceImage{resourceName};

                pieceImage.render(&painter, QRect(x, y, _cellsSize, _cellsSize));
            }

        }
    }

    // paiting last move arrow
    if (_lastMoveCoordinates != nullptr)
    {
        drawArrowBetweenCells(painter, lastMoveArrowColor, _lastMoveCoordinates->startFile, _lastMoveCoordinates->startRank,
                              _lastMoveCoordinates->endFile, _lastMoveCoordinates->endRank);
    }

    // painting coordinates
    const auto fontSize = _cellsSize * 0.3;
    const auto coordinatesColor = QColor(255, 199, 0);
    auto font = QFont();
    font.setPointSizeF(fontSize);
    font.setWeight(QFont::Bold);
    painter.setFont(font);
    painter.setPen(QPen(coordinatesColor));

    const auto ascii_a = 65;
    const auto ascii_1 = 49;

    for (auto col: colsIndexes)
    {
        const auto file = _reversed ? 7-col : col;
        const auto letter = static_cast<char>(ascii_a + file);

        const auto x = int(floor(_cellsSize * (0.85 + col)));
        const auto y1 = int(floor(_cellsSize * 0.4));
        const auto y2 = int(floor(_cellsSize * 8.9));

        painter.drawText(x, y1, QString(letter));
        painter.drawText(x, y2, QString(letter));
    }

    for (auto row: rowsIndexes)
    {
        const auto rank = _reversed ? row : 7-row;
        const auto digit = static_cast<char>(ascii_1 + rank);

        const auto x1 = int(floor(_cellsSize * 0.12));
        const auto x2 = int(floor(_cellsSize * 8.62));
        const auto y = int(floor(_cellsSize * (1.2 + row)));

        painter.drawText(x1, y, QString(digit));
        painter.drawText(x2, y, QString(digit));
    }

    // Painting player turn
    const auto turnColor = _relatedPosition->isWhiteTurn() ? Qt::white : Qt::black;
    const auto location = int(floor(_cellsSize * 8.55));
    const auto turnSize = int(floor(_cellsSize * 0.4));
    painter.setBrush(turnColor);
    painter.setPen(QPen(Qt::transparent));
    painter.drawEllipse(location, location, turnSize, turnSize);

    // painting the moved piece if any
    if (_dndData != nullptr) {
        auto resourceName = QString(":/chess_vectors/");
        resourceName += IPosition::pieceFenToPieceImageReference(_dndData->pieceFen);
        QSvgRenderer movedPieceImage{resourceName};

        movedPieceImage.render(&painter, QRect(_dndData->pieceX, _dndData->pieceY, _cellsSize, _cellsSize));
    }
}

void ChessBoard::mousePressEvent(QMouseEvent *event)
{
    if (_gameFinishedStatus != GameFinishedStatus::NOT_FINISHED) return;

    const auto whiteTurn = _relatedPosition->isWhiteTurn();
    const auto playerIsHuman = (whiteTurn && (_whitePlayer == PlayerType::HUMAN)) ||
            (!whiteTurn && (_blackPlayer == PlayerType::HUMAN));
    if (!playerIsHuman) return;

    const auto x = event->x();
    const auto y = event->y();

    const auto col = int(floor((x*1.0 - _cellsSize*0.5) / _cellsSize));
    const auto row = int(floor((y*1.0 - _cellsSize*0.5) / _cellsSize));

    const auto file = _reversed ? 7-col : col;
    const auto rank = _reversed ? row : 7-row;

    if (file < 0 || file > 7 || rank < 0 || rank > 7) return;
    const auto movedPiece = _relatedPosition->getPieceFenAt(file, rank);
    const auto isEmptyPiece = ! QVector<char>{
        'P', 'N', 'B', 'R', 'Q', 'K',
        'p', 'n', 'b', 'r', 'q', 'k'
    }.contains(movedPiece);

    if (isEmptyPiece) return;

    // We must not called isupper with a moved piece not belonging to the FEN set,
    // as it may have a value causing an undefined behaviour.
    const auto isAWhitePiece = isupper(movedPiece) > 0;
    const auto isAPieceOfSideInTurn = isAWhitePiece == _relatedPosition->isWhiteTurn();

    if (! isAPieceOfSideInTurn) return;

    _dndData = new DndData(movedPiece, file, rank, x, y);
    _dndData->pointerInBounds = true;

   repaint();
}

void ChessBoard::mouseMoveEvent(QMouseEvent *event)
{
    if (_gameFinishedStatus != GameFinishedStatus::NOT_FINISHED) return;
    if (_dndData == nullptr) return;

    const auto x = event->x();
    const auto y = event->y();

    const auto col = int(floor((x*1.0 - _cellsSize*0.5) / _cellsSize));
    const auto row = int(floor((y*1.0 - _cellsSize*0.5) / _cellsSize));

    const auto file = _reversed ? 7-col : col;
    const auto rank = _reversed ? row : 7-row;

    _dndData->pieceX = x;
    _dndData->pieceY = y;

    if (file < 0 || file > 7 || rank < 0 || rank > 7) {
        _dndData->pointerInBounds = false;
        repaint();
        return;
    }

    _dndData->endFile = file;
    _dndData->endRank = rank;
    _dndData->pointerInBounds = true;

    repaint();
}

void ChessBoard::mouseReleaseEvent(QMouseEvent *event)
{
    if (_gameFinishedStatus != GameFinishedStatus::NOT_FINISHED) return;
    if (_dndData == nullptr) return;

    const auto x = event->x();
    const auto y = event->y();

    const auto col = int(floor((x*1.0 - _cellsSize*0.5) / _cellsSize));
    const auto row = int(floor((y*1.0 - _cellsSize*0.5) / _cellsSize));

    const auto file = _reversed ? 7-col : col;
    const auto rank = _reversed ? row : 7-row;

    const auto startFile = _dndData->startFile;
    const auto startRank = _dndData->startRank;

    _dndData->pieceX = x;
    _dndData->pieceY = y;
    repaint();

    const auto clearDndData = [this]()
    {
        if (_dndData != nullptr) {
            delete _dndData;
            _dndData = nullptr;
        }
    };

    if (file < 0 || file > 7 || rank < 0 || rank > 7) {
        clearDndData();
        repaint();
        return;
    }

    const auto localUpdateLastMove = [this, file, rank]()
    {
        if (_dndData != nullptr)
        {
            updateLastMove(_dndData->startFile, _dndData->startRank, file, rank);
        }
    };

    bool isPromotionMove{_relatedPosition->isPromotionMove(startFile, startRank, file, rank)};
    if (isPromotionMove)
    {
        PromotionDialog promotionDialog(this, _relatedPosition->isWhiteTurn(), _cellsSize);

        connect(&promotionDialog, &PromotionDialog::validateQueenPromotion, this,
                [=, &promotionDialog](){
            const auto moveSan = _relatedPosition->getMoveSan(startFile, startRank, file, rank, 'q');
            const auto moveFan = _relatedPosition->getMoveFan(startFile, startRank, file, rank, 'q');

            try {
                _relatedPosition->makeMove(startFile, startRank, file ,rank, 'q');

                const auto resultingFen = QString(_relatedPosition->getFen().c_str());
                MoveCoordinates lastMoveCoords(startFile, startRank, file, rank);

                localUpdateLastMove();
                clearDndData();
                repaint();
                promotionDialog.hide();
                handleGameFinished();

                const auto gameFinished = ! gameInProgress();
                emit moveDoneAsSan(moveSan, resultingFen, lastMoveCoords, gameFinished);
                emit moveDoneAsFan(moveFan, resultingFen, lastMoveCoords, gameFinished);
                emitExternalPlayerTurnIfNecessary();

                showGameFinishedMessageIfNecessary();
            } catch (const IllegalMoveException &/* e*/) {}
        });
        connect(&promotionDialog, &PromotionDialog::validateRookPromotion, this,
                [=, &promotionDialog](){
            const auto moveSan = _relatedPosition->getMoveSan(startFile, startRank, file, rank, 'r');
            const auto moveFan = _relatedPosition->getMoveFan(startFile, startRank, file, rank, 'r');

            try {
                _relatedPosition->makeMove(startFile, startRank, file ,rank, 'r');

                const auto resultingFen = QString(_relatedPosition->getFen().c_str());
                MoveCoordinates lastMoveCoords(startFile, startRank, file, rank);

                localUpdateLastMove();
                clearDndData();
                repaint();
                promotionDialog.hide();
                handleGameFinished();

                const auto gameFinished = ! gameInProgress();
                emit moveDoneAsSan(moveSan, resultingFen, lastMoveCoords, gameFinished);
                emit moveDoneAsFan(moveFan, resultingFen, lastMoveCoords, gameFinished);
                emitExternalPlayerTurnIfNecessary();

                showGameFinishedMessageIfNecessary();
            }
            catch (const IllegalMoveException &/* e */){}
        });
        connect(&promotionDialog, &PromotionDialog::validateBishopPromotion, this,
                [=, &promotionDialog](){
            const auto moveSan = _relatedPosition->getMoveSan(startFile, startRank, file, rank, 'b');
            const auto moveFan = _relatedPosition->getMoveFan(startFile, startRank, file, rank, 'b');

            try {
                _relatedPosition->makeMove(startFile, startRank, file ,rank, 'b');

                const auto resultingFen = QString(_relatedPosition->getFen().c_str());
                MoveCoordinates lastMoveCoords(startFile, startRank, file, rank);

                localUpdateLastMove();
                clearDndData();
                repaint();
                promotionDialog.hide();
                handleGameFinished();

                const auto gameFinished = ! gameInProgress();
                emit moveDoneAsSan(moveSan, resultingFen, lastMoveCoords, gameFinished);
                emit moveDoneAsFan(moveFan, resultingFen, lastMoveCoords, gameFinished);
                emitExternalPlayerTurnIfNecessary();

                showGameFinishedMessageIfNecessary();
            } catch (const IllegalMoveException & /* e */){}

        });
        connect(&promotionDialog, &PromotionDialog::validateKnightPromotion, this,
                [=, &promotionDialog](){
            const auto moveSan = _relatedPosition->getMoveSan(startFile, startRank, file, rank, 'n');
            const auto moveFan = _relatedPosition->getMoveFan(startFile, startRank, file, rank, 'n');

            try {
                _relatedPosition->makeMove(startFile, startRank, file, rank, 'n');

                const auto resultingFen = QString(_relatedPosition->getFen().c_str());
                MoveCoordinates lastMoveCoords(startFile, startRank, file, rank);

                localUpdateLastMove();
                clearDndData();
                repaint();
                promotionDialog.hide();
                handleGameFinished();

                const auto gameFinished = ! gameInProgress();
                emit moveDoneAsSan(moveSan, resultingFen, lastMoveCoords, gameFinished);
                emit moveDoneAsFan(moveFan, resultingFen, lastMoveCoords, gameFinished);
                emitExternalPlayerTurnIfNecessary();

                showGameFinishedMessageIfNecessary();
            } catch (const IllegalMoveException & /* e */) {}
        });

        promotionDialog.exec();
        return;
    }

    try
    {
        const auto moveSan = _relatedPosition->getMoveSan(startFile, startRank, file, rank);
        const auto moveFan = _relatedPosition->getMoveFan(startFile, startRank, file, rank);

        _relatedPosition->makeMove(startFile, startRank, file, rank);

        const auto resultingFen = QString(_relatedPosition->getFen().c_str());
        MoveCoordinates lastMoveCoords(startFile, startRank, file, rank);

        localUpdateLastMove();
        clearDndData();
        repaint();
        handleGameFinished();

        const auto gameFinished = ! gameInProgress();
        emit moveDoneAsSan(moveSan, resultingFen, lastMoveCoords, gameFinished);
        emit moveDoneAsFan(moveFan, resultingFen, lastMoveCoords, gameFinished);
        emitExternalPlayerTurnIfNecessary();

        showGameFinishedMessageIfNecessary();
    }
    catch (const IllegalMoveException & /* e */)
    {
        clearDndData();
        repaint();
    }
}

bool loloof64::ChessBoard::setPosition(const HistoryItem historyItem)
{
    if (_gameFinishedStatus == GameFinishedStatus::NOT_FINISHED) return false;

    if (_relatedPosition != nullptr)
    {
        delete _relatedPosition;
        _relatedPosition = nullptr;
    }

    try {
        _relatedPosition = new ThcPosition(historyItem.newPositionFen.toStdString());
    } catch (IllegalPositionException & /* e */) {
        return false;
    }

    if (_lastMoveCoordinates != nullptr)
    {
        delete _lastMoveCoordinates;
        _lastMoveCoordinates = nullptr;
    }

    bool lastMoveCanBeSet = historyItem.lastMove.startFile > -1 && historyItem.lastMove.startRank > -1 &&
            historyItem.lastMove.endFile > -1 && historyItem.lastMove.endRank > -1;
    if (lastMoveCanBeSet) {
        _lastMoveCoordinates = new MoveCoordinates(historyItem.lastMove);
    }

    repaint();

    return true;
}

bool loloof64::ChessBoard::playMove(int startFile, int startRank, int endFile, int endRank, char promotionFen)
{
    if (!gameInProgress()) return false;

    const auto whiteTurn = _relatedPosition->isWhiteTurn();
    const auto isHumanPlayer = (whiteTurn && (_whitePlayer == PlayerType::HUMAN)) ||
            (!whiteTurn && (_blackPlayer == PlayerType::HUMAN));
    if (isHumanPlayer) return false;

    try
    {
        const auto moveSan = _relatedPosition->getMoveSan(startFile, startRank, endFile, endRank);
        const auto moveFan = _relatedPosition->getMoveFan(startFile, startRank, endFile, endRank);

        _relatedPosition->makeMove(startFile, startRank, endFile, endRank, promotionFen);
        const auto resultingFen = QString(_relatedPosition->getFen().c_str());

        MoveCoordinates lastMoveCoords(startFile, startRank, endFile, endRank);
        updateLastMove(startFile, startRank, endFile, endRank);
        repaint();

        handleGameFinished();

        const auto gameFinished = ! gameInProgress();
        emit moveDoneAsSan(moveSan, resultingFen, lastMoveCoords, gameFinished);
        emit moveDoneAsFan(moveFan, resultingFen, lastMoveCoords, gameFinished);
        emitExternalPlayerTurnIfNecessary();

        showGameFinishedMessageIfNecessary();

        return true;
    }
    catch (UnimplementedException const * /* e */)
    {
        return false;
    }
}

void loloof64::ChessBoard::emitExternalPlayerTurnIfNecessary()
{
    const auto whiteTurn = _relatedPosition->isWhiteTurn();
    const auto isExternalTurn = (whiteTurn && (_whitePlayer == PlayerType::EXTERNAL)) ||
            (!whiteTurn && (_blackPlayer == PlayerType::EXTERNAL));
    if (!isExternalTurn) return;

    const auto currentPosition = QString(_relatedPosition->getFen().c_str());
    emit externalTurn(currentPosition);
}

void loloof64::ChessBoard::updateLastMove(int startFile, int startRank, int endFile, int endRank)
{
    if (_lastMoveCoordinates != nullptr)
    {
        delete _lastMoveCoordinates;
        _lastMoveCoordinates = nullptr;
    }
    _lastMoveCoordinates = new MoveCoordinates(startFile, startRank, endFile, endRank);
}


void loloof64::ChessBoard::handleGameFinished()
{
    const auto isCheckmate = _relatedPosition->isCheckmate();
    const auto isStalemate = _relatedPosition->isStalemate();
    const auto isDrawByThreeFolds = _relatedPosition->isThreeFoldRepetitionsDraw();
    const auto isInsuficientMaterial = _relatedPosition->isInsuficientMaterialDraw();
    const auto isFiftyMovesRuleDraw = _relatedPosition->isFiftyMovesRuleDraw();

    if (isCheckmate)
    {
        _gameFinishedStatus = GameFinishedStatus::CHECKMATE;
    }
    else if (isStalemate)
    {
        _gameFinishedStatus = GameFinishedStatus::STALEMATE;
    }
    else if (isDrawByThreeFolds)
    {
        _gameFinishedStatus = GameFinishedStatus::REPETITIONS;
    }
    else if (isInsuficientMaterial)
    {
        _gameFinishedStatus = GameFinishedStatus::INSUFICIENT_MATERIAL;
    }
    else if (isFiftyMovesRuleDraw)
    {
        _gameFinishedStatus = GameFinishedStatus::FIFTY_MOVES_RULE;
    }
}

void loloof64::ChessBoard::showGameFinishedMessageIfNecessary()
{
    switch (_gameFinishedStatus) {
    case GameFinishedStatus::CHECKMATE:
        emit gameEnded();
        QMessageBox::information(this, tr("Game finished", "Game finished modal title"), tr("Checkmate"));
        break;
    case GameFinishedStatus::STALEMATE:
        emit gameEnded();
        QMessageBox::information(this, tr("Game finished", "Game finished modal title"), tr("Stalemate"));
        break;
    case GameFinishedStatus::REPETITIONS:
        emit gameEnded();
        QMessageBox::information(this, tr("Game finished", "Game finished modal title"), tr("Draw by 3-folds repetition"));
        break;
    case GameFinishedStatus::INSUFICIENT_MATERIAL:
        emit gameEnded();
        QMessageBox::information(this, tr("Game finished", "Game finished modal title"), tr("Draw by insuficient material"));
        break;
    case GameFinishedStatus::FIFTY_MOVES_RULE:
        emit gameEnded();
        QMessageBox::information(this, tr("Game finished", "Game finished modal title"), tr("Draw by the 50 moves rule"));
        break;
    default:
        break;
    }
}

void loloof64::ChessBoard::drawArrowBetweenCells(QPainter &painter, QColor color, int startFile, int startRank, int endFile, int endRank)
{
    QPen pen = color;
    pen.setWidth(int(floor(_cellsSize * 0.2)));
    painter.setPen(pen);

    const auto startCol = _reversed ? 7-startFile : startFile;
    const auto startRow = _reversed ? startRank : 7-startRank;
    const auto endCol = _reversed ? 7-endFile : endFile;
    const auto endRow = _reversed ? endRank : 7-endRank;

    const auto deltaX = endCol - startCol;
    const auto deltaY = endRow - startRow;
    const auto baseLineLength = sqrt(deltaX*deltaX + deltaY*deltaY);
    const auto baseLineAngleDegrees = atan2(deltaY, deltaX) * 180.0 / 3.1415927;
    const auto arrowLineLength = int(floor(baseLineLength * 10));

    const auto baseLineStartX = int(floor(_cellsSize * (startCol + 1)));
    const auto baseLineStartY = int(floor(_cellsSize * (startRow + 1)));
    const auto baseLineEndX = int(floor(_cellsSize * (endCol + 1)));
    const auto baseLineEndY = int(floor(_cellsSize * (endRow + 1)));

    const auto arrowAngleRad = 30 * 3.1415926 / 180.0;
    const auto arrowLineEndX = -int(floor(arrowLineLength * cos(arrowAngleRad)));
    const auto arrowLineEndY = int(floor(arrowLineLength * sin(arrowAngleRad)));


    painter.drawLine(
        baseLineStartX, baseLineStartY,
        baseLineEndX, baseLineEndY
    );

    painter.save();
    painter.translate(baseLineEndX, baseLineEndY);
    painter.rotate(baseLineAngleDegrees);

    painter.drawLine(0, 0, arrowLineEndX, arrowLineEndY);
    painter.drawLine(0, 0, arrowLineEndX, -arrowLineEndY);

    painter.restore();
}

void loloof64::ChessBoard::setWhitePlayerType(PlayerType playerType)
{
    _whitePlayer = playerType;
}

void loloof64::ChessBoard::setBlackPlayerType(PlayerType playerType)
{
    _blackPlayer = playerType;
}

QString loloof64::ChessBoard::getMoveSan(int startFile, int startRank, int endFile, int endRank, char promotionFen) const
{
    return _relatedPosition->getMoveSan(startFile, startRank, endFile, endRank, promotionFen);
}


QString loloof64::ChessBoard::getMoveFan(int startFile, int startRank, int endFile, int endRank, char promotionFen) const
{
    return _relatedPosition->getMoveFan(startFile, startRank, endFile, endRank, promotionFen);
}

QString loloof64::ChessBoard::getCurrentPosition() const
{
    return QString::fromStdString(_relatedPosition->getFen());
}
