#include "chessboard.h"
#include <QPainter>
#include <QVector>
#include <QString>
#include <cmath>

ChessBoard::ChessBoard(int cellsSize, QWidget* parent) : QWidget(parent), _cellsSize(cellsSize)
{
    auto wholeSize = 9 * cellsSize;
    setFixedSize(wholeSize, wholeSize);
}

ChessBoard::~ChessBoard()
{
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
            const auto isWhiteCell = (row+col) %2 == 0;
            const auto x = floor(_cellsSize * (0.5 + col));
            const auto y = floor(_cellsSize * (0.5 + row));
            const auto cellColor = isWhiteCell ? whiteCellsColor : blackCellsColor;

            painter.fillRect(x, y, _cellsSize, _cellsSize, cellColor);
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
        const auto file = col;
        const auto letter = (char) (ascii_a + file);

        const auto x = floor(_cellsSize * (0.85 + col));
        const auto y1 = floor(_cellsSize * 0.4);
        const auto y2 = floor(_cellsSize * 8.9);

        painter.drawText(x, y1, QString(letter));
        painter.drawText(x, y2, QString(letter));
    }

    for (auto row: rowsIndexes)
    {
        const auto rank = 7-row;
        const auto digit = (char) (ascii_1 + rank);

        const auto x1 = floor(_cellsSize * 0.12);
        const auto x2 = floor(_cellsSize * 8.62);
        const auto y = floor(_cellsSize * (1.2 + row));

        painter.drawText(x1, y, QString(digit));
        painter.drawText(x2, y, QString(digit));
    }
}
