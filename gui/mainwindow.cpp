#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _board = new loloof64::ChessBoard(60, this);
    _mainToolBar = new QToolBar;

    _mainToolBar->addAction(QIcon(QPixmap(":/icons/swap.svg")), QString(tr("Toggle side")), [this](){
        this->_board->reverse();
    });
    _mainToolBar->addAction(QIcon(QPixmap(":/icons/start.svg")), QString(tr("New game")), [this](){
        this->_board->newGame();
    });

    addToolBar(_mainToolBar);
    setCentralWidget(_board);
}

MainWindow::~MainWindow()
{
    delete _mainToolBar;
    delete _board;
}

