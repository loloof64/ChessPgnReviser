#ifndef GAMESELECTIONDIALOG_H
#define GAMESELECTIONDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include "gameselectionmainzone.h"

namespace loloof64
{
    class GameSelectionDialog : public QDialog
    {
        Q_OBJECT
    public:
        explicit GameSelectionDialog(QWidget *parent = nullptr);
        ~GameSelectionDialog();

    signals:

    private:
        QVBoxLayout *_layout;
        QLabel *_gameIndexLabel;
        QLabel *_playersLabel;
        QLabel *_eventLabel;
        GameSelectionMainZone *_mainZone;
    };
};

#endif // GAMESELECTIONDIALOG_H
