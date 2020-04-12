#include "chessboard.h"
#include "promotiondialog.h"
#include "../adapters/thcposition.h"
#include <QPainter>
#include <QVector>
#include <QString>
#include <QSvgRenderer>
#include <cmath>
#include <cctype>

#include <QMessageLogger>

using namespace loloof64;

QString pieceFenToPieceImageReference(char pieceFen)
{
    switch (pieceFen) {
        case 'P': return "pl.svg";
        case 'N': return "nl.svg";
        case 'B': return "bl.svg";
        case 'R': return "rl.svg";
        case 'Q': return "ql.svg";
        case 'K': return "kl.svg";

        case 'p': return "pd.svg";
        case 'n': return "nd.svg";
        case 'b': return "bd.svg";
        case 'r': return "rd.svg";
        case 'q': return "qd.svg";
        case 'k': return "kd.svg";

    default:
        return "";
    }
}

ChessBoard::ChessBoard(int cellsSize, QWidget* parent) : QWidget(parent), _cellsSize(cellsSize)
{
    _relatedPosition = new ThcPosition();
    _dndData = nullptr;
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

void ChessBoard::paintEvent(QPaintEvent * /* event */)
{
    const auto wholeSize = 9 * _cellsSize;
    const auto colsIndexes = QVector<int>{0,1,2,3,4,5,6,7};
    const auto rowsIndexes = QVector<int>{0,1,2,3,4,5,6,7};

    const auto backgroundColor = QColor(108, 93, 167);
    const auto whiteCellsColor = QColor(255, 206, 158);
    const auto blackCellsColor = QColor(209, 139, 71);
    const auto dndCrossCellColor = QColor(200, 115, 207);
    const auto dndStartCellColor = Qt::green;
    const auto dndEndCellColor = Qt::red;
    const auto lastMoveArrowColor = QColor(0, 0, 255, 100);
    const auto lastMoveArrowPointerColor = QColor(255, 0, 0, 160);

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
            const auto x = floor(_cellsSize * (0.5 + col));
            const auto y = floor(_cellsSize * (0.5 + row));
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
                resourceName += pieceFenToPieceImageReference(pieceValue);
                QSvgRenderer pieceImage{resourceName};

                pieceImage.render(&painter, QRect(x, y, _cellsSize, _cellsSize));
            }

        }
    }

    // paiting last move arrow
    if (_lastMoveCoordinates != nullptr)
    {
        QPen pen{lastMoveArrowColor};
        pen.setWidth(floor(_cellsSize * 0.2));
        painter.setPen(pen);

        const auto startCol = _reversed ? 7-_lastMoveCoordinates->startFile : _lastMoveCoordinates->startFile;
        const auto startRow = _reversed ? _lastMoveCoordinates->startRank : 7-_lastMoveCoordinates->startRank;
        const auto endCol = _reversed ? 7-_lastMoveCoordinates->endFile : _lastMoveCoordinates->endFile;
        const auto endRow = _reversed ? _lastMoveCoordinates->endRank : 7-_lastMoveCoordinates->endRank;

        painter.drawLine(
            floor(_cellsSize * (startCol + 1)),
            floor(_cellsSize * (startRow + 1)),
            floor(_cellsSize * (endCol + 1)),
            floor(_cellsSize * (endRow + 1))
        );

        painter.setBrush(QBrush(lastMoveArrowPointerColor));
        painter.drawEllipse(
            floor(_cellsSize * (endCol + 0.75)),
            floor(_cellsSize * (endRow + 0.75)),
            floor(_cellsSize * 0.5),
            floor(_cellsSize * 0.5)
        );
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
        const auto letter = (char) (ascii_a + file);

        const auto x = floor(_cellsSize * (0.85 + col));
        const auto y1 = floor(_cellsSize * 0.4);
        const auto y2 = floor(_cellsSize * 8.9);

        painter.drawText(x, y1, QString(letter));
        painter.drawText(x, y2, QString(letter));
    }

    for (auto row: rowsIndexes)
    {
        const auto rank = _reversed ? row : 7-row;
        const auto digit = (char) (ascii_1 + rank);

        const auto x1 = floor(_cellsSize * 0.12);
        const auto x2 = floor(_cellsSize * 8.62);
        const auto y = floor(_cellsSize * (1.2 + row));

        painter.drawText(x1, y, QString(digit));
        painter.drawText(x2, y, QString(digit));
    }

    // Painting player turn
    const auto turnColor = _relatedPosition->isWhiteTurn() ? Qt::white : Qt::black;
    const auto location = floor(_cellsSize * 8.55);
    const auto turnSize = floor(_cellsSize * 0.4);
    painter.setBrush(turnColor);
    painter.setPen(QPen(Qt::transparent));
    painter.drawEllipse(location, location, turnSize, turnSize);

    // painting the moved piece if any
    if (_dndData != nullptr) {
        auto resourceName = QString(":/chess_vectors/");
        resourceName += pieceFenToPieceImageReference(_dndData->pieceFen);
        QSvgRenderer movedPieceImage{resourceName};

        movedPieceImage.render(&painter, QRect(_dndData->pieceX, _dndData->pieceY, _cellsSize, _cellsSize));
    }
}

void ChessBoard::mousePressEvent(QMouseEvent *event)
{
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

    const auto updateLastMove = [this, file, rank]()
    {
       if (_lastMoveCoordinates != nullptr) delete _lastMoveCoordinates;
       if (_dndData != nullptr) {
            _lastMoveCoordinates = new LastMoveCoordinates(_dndData->startFile, _dndData->startRank, file, rank);
       }
    };

    bool isPromotionMove{_relatedPosition->isPromotionMove(startFile, startRank, file, rank)};
    if (isPromotionMove)
    {
        PromotionDialog promotionDialog(this, _relatedPosition->isWhiteTurn(), _cellsSize);

        connect(&promotionDialog, &PromotionDialog::validateQueenPromotion, this,
                [=, &promotionDialog](){
            const auto newPositionFen = _relatedPosition->makeMove(startFile, startRank, file ,rank, 'q');
            delete _relatedPosition;
            _relatedPosition = new ThcPosition(newPositionFen);
            updateLastMove();
            clearDndData();
            repaint();
            promotionDialog.hide();
        });
        connect(&promotionDialog, &PromotionDialog::validateRookPromotion, this,
                [=, &promotionDialog](){
            const auto newPositionFen = _relatedPosition->makeMove(startFile, startRank, file ,rank, 'r');
            delete _relatedPosition;
            _relatedPosition = new ThcPosition(newPositionFen);
            updateLastMove();
            clearDndData();
            repaint();
            promotionDialog.hide();
        });
        connect(&promotionDialog, &PromotionDialog::validateBishopPromotion, this,
                [=, &promotionDialog](){
            const auto newPositionFen = _relatedPosition->makeMove(startFile, startRank, file ,rank, 'b');
            delete _relatedPosition;
            _relatedPosition = new ThcPosition(newPositionFen);
            updateLastMove();
            clearDndData();
            repaint();
            promotionDialog.hide();
        });
        connect(&promotionDialog, &PromotionDialog::validateKnightPromotion, this,
                [=, &promotionDialog](){
            const auto newPositionFen = _relatedPosition->makeMove(startFile, startRank, file, rank, 'n');
            delete _relatedPosition;
            _relatedPosition = new ThcPosition(newPositionFen);
            updateLastMove();
            clearDndData();
            repaint();
            promotionDialog.hide();
        });

        promotionDialog.exec();
        return;
    }

    try
    {
        const auto newPositionFen = _relatedPosition->makeMove(startFile, startRank, file, rank);
        delete _relatedPosition;
        _relatedPosition = new ThcPosition(newPositionFen);
        updateLastMove();
        clearDndData();
        repaint();
    }
    catch (IllegalMoveException const *e)
    {
        clearDndData();
        repaint();
    }
}
