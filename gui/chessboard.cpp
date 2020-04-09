#include "chessboard.h"
#include <QPainter>

ChessBoard::ChessBoard(int cellsSize, QWidget* parent) : QWidget(parent), _cellsSize(cellsSize)
{
    auto wholeSize = 9 * cellsSize;
    setFixedSize(wholeSize, wholeSize);

    _backgroundColor = new QColor(108, 93, 167);
}

ChessBoard::~ChessBoard()
{
    delete _backgroundColor;
}

void ChessBoard::paintEvent(QPaintEvent * /* event */)
{
    auto wholeSize = 9 * _cellsSize;

    QPainter painter(this);
    painter.fillRect(0, 0, wholeSize, wholeSize, *_backgroundColor);
}
