#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _board = new loloof64::ChessBoard(40, this);

    _board->show();
    setCentralWidget(_board);
}

MainWindow::~MainWindow()
{
    delete _board;
}

