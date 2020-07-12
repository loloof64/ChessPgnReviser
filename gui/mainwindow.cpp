#include "mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _componentsZone = new loloof64::ComponentsZone(this);
    _mainToolBar = new QToolBar;

    _mainToolBar->addAction(QIcon(QPixmap(":/icons/start.svg")), QString(tr("New game", "Caption for the button 'new game'")), [this](){
        if (! _componentsZone->gameInProgress()) {
            this->_componentsZone->newGame();
            return;
        }
        int confirmation = QMessageBox::question(this,
                                                 tr("Confirm stop game ?", "Confirm stop game modal title"),
                                                 tr("Are you sure you want to stop the current game ?", "Confirm stop game modal text"),
                            QMessageBox::Yes | QMessageBox::No);
        if (confirmation == QMessageBox::Yes) this->_componentsZone->newGame();
    });
    _mainToolBar->addAction(QIcon(QPixmap(":/icons/stop.svg")), QString(tr("Stop game", "Caption for the button 'stop game'")), [this](){
        if (! _componentsZone->gameInProgress()) return;
        int confirmation = QMessageBox::question(this,
                                                 tr("Confirm stop game ?", "Confirm stop game modal title"),
                                                 tr("Are you sure you want to stop the current game ?", "Confirm stop game modal text"),
                            QMessageBox::Yes | QMessageBox::No);
        if (confirmation == QMessageBox::Yes) this->_componentsZone->stopGame();
    });
    _mainToolBar->addAction(QIcon(QPixmap(":/icons/swap.svg")), QString(tr("Toggle side", "Caption for the button 'toggle side'")), [this](){
        this->_componentsZone->reverseBoard();
    });

    addToolBar(_mainToolBar);
    setCentralWidget(_componentsZone);

    setFixedSize(1150, 600);
}

MainWindow::~MainWindow()
{
    delete _mainToolBar;
    delete _componentsZone;
}

