#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>

class ChessBoard : public QWidget
{
    Q_OBJECT
public:
    explicit ChessBoard(int cellsSize, QWidget *parent);
    ~ChessBoard();

signals:

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int _cellsSize;
    QColor* _backgroundColor;
};

#endif // CHESSBOARD_H
