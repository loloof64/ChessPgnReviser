#include "mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _board = new loloof64::ChessBoard(60, this);
    _mainToolBar = new QToolBar;

    _mainToolBar->addAction(QIcon(QPixmap(":/icons/swap.svg")), QString(tr("Toggle side", "Caption for the button 'toggle side'")), [this](){
        this->_board->reverse();
    });
    _mainToolBar->addAction(QIcon(QPixmap(":/icons/start.svg")), QString(tr("New game", "Caption for the button 'new game'")), [this](){
        this->_board->newGame();
    });
    _mainToolBar->addAction(QIcon(QPixmap(":/icons/stop.svg")), QString(tr("Stop game", "Caption for the button 'stop game'")), [this](){
        if (! _board->gameInProgress()) return;
        int confirmation = QMessageBox::question(this,
                                                 tr("Confirm stop game ?", "Confirm stop game modal title"),
                                                 tr("Are you sure you want to stop the current game ?", "Confirm stop game modal text"),
                            QMessageBox::Yes | QMessageBox::No);
        if (confirmation == QMessageBox::Yes) this->_board->stopGame();
    });

    addToolBar(_mainToolBar);
    setCentralWidget(_board);
}

MainWindow::~MainWindow()
{
    delete _mainToolBar;
    delete _board;
}

