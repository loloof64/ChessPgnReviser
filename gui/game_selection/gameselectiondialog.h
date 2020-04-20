#ifndef GAMESELECTIONDIALOG_H
#define GAMESELECTIONDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QComboBox>
#include <QPushButton>
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
        QPushButton *_validateButton;

        QHBoxLayout *_whitePlayerSelectionLineLayout;
        QHBoxLayout *_blackPlayerSelectionLineLayout;
        QFrame *_whitePlayerSelectionLine;
        QFrame *_blackPlayerSelectionLine;
        QLabel *_whitePlayerSelectionLabel;
        QLabel *_blackPlayerSelectionLabel;
        QComboBox *_whitePlayerSelectionCombo;
        QComboBox *_blackPlayerSelectionCombo;
    };
};

#endif // GAMESELECTIONDIALOG_H
