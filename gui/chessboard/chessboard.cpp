#include "chessboard.h"
#include "../adapters/thcposition.h"
#include <QPainter>
#include <QVector>
#include <QString>
#include <cmath>
#include <QSvgRenderer>

#include <QMessageLogger>

using namespace loloof64;

ChessBoard::ChessBoard(int cellsSize, QWidget* parent) : QWidget(parent), _cellsSize(cellsSize)
{
    _relatedPosition = new ThcPosition();
    auto wholeSize = 9 * cellsSize;
    setFixedSize(wholeSize, wholeSize);
}

ChessBoard::~ChessBoard()
{
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

    QPainter painter(this);

    // painting background
    painter.fillRect(0, 0, wholeSize, wholeSize, backgroundColor);

    // painting cells
    for (auto row: rowsIndexes)
    {
        for (auto col: colsIndexes)
        {
            // draw cell
            const auto isWhiteCell = (row+col) %2 == 0;
            const auto x = floor(_cellsSize * (0.5 + col));
            const auto y = floor(_cellsSize * (0.5 + row));
            const auto cellColor = isWhiteCell ? whiteCellsColor : blackCellsColor;

            painter.fillRect(x, y, _cellsSize, _cellsSize, cellColor);

            // draw piece
            const auto file = _reversed ? 7-col : col;
            const auto rank = _reversed ? row : 7-row;
            const auto pieceValue = _relatedPosition->getPieceFenAt(file, rank);

            const auto notAnEmptyPiece = QVector<char>{
                'P', 'N', 'B', 'R', 'Q', 'K',
                'p', 'n', 'b', 'r', 'q', 'k'
            }.contains(pieceValue);

            if (notAnEmptyPiece)
            {
                auto resourceName = QString(":/chess_vectors/");
                switch (pieceValue) {
                    case 'P': resourceName += "pl.svg"; break;
                    case 'N': resourceName += "nl.svg"; break;
                    case 'B': resourceName += "bl.svg"; break;
                    case 'R': resourceName += "rl.svg"; break;
                    case 'Q': resourceName += "ql.svg"; break;
                    case 'K': resourceName += "kl.svg"; break;

                    case 'p': resourceName += "pd.svg"; break;
                    case 'n': resourceName += "nd.svg"; break;
                    case 'b': resourceName += "bd.svg"; break;
                    case 'r': resourceName += "rd.svg"; break;
                    case 'q': resourceName += "qd.svg"; break;
                    case 'k': resourceName += "kd.svg"; break;
                }
                QSvgRenderer pieceImage{resourceName};

                pieceImage.render(&painter, QRect(x, y, _cellsSize, _cellsSize));
            }

        }
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
}
