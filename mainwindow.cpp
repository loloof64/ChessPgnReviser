#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _board = new ChessBoard(60, this);

    _board->show();
    setCentralWidget(_board);
}

MainWindow::~MainWindow()
{
    delete _board;
}

