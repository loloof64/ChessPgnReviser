#include "chessboard.h"
#include <QPainter>
#include <QVector>
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
        for (auto col: rowsIndexes)
        {
            const auto isWhiteCell = (row+col) %2 == 0;
            const auto x = floor(_cellsSize * (0.5 + col));
            const auto y = floor(_cellsSize * (0.5 + row));
            const auto cellColor = isWhiteCell ? whiteCellsColor : blackCellsColor;

            painter.fillRect(x, y, _cellsSize, _cellsSize, cellColor);
        }
    }
}
