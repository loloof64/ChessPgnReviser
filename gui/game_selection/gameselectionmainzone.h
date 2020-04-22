#ifndef GAMESELECTIONMAINZONE_H
#define GAMESELECTIONMAINZONE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFrame>
#include <QLineEdit>
#include <QValidator>
#include "../chessboard/chessboard.h"
#include "../../libs/chessx-pgn/database/pgndatabase.h"

namespace loloof64 {
    class GameSelectionMainZone : public QWidget
    {
        Q_OBJECT
    public:
        explicit GameSelectionMainZone(QWidget *parent = nullptr);
        ~GameSelectionMainZone();
        void setPgnDatabase(PgnDatabase *database);

        quint64 getSelectedGameIndex() const;

    signals:
        void gameIndexChanged(quint64 index);
        void whitePlayerChanged(QString name);
        void blackPlayerChanged(QString name);
        void gameEventChanged(QString name);
        void gameDateChanged(QString date);
        void gameSiteChanged(QString site);

    private:
        quint64 _selectedGameIndex;
        QFrame *_mainZone;
        QLineEdit *_gameTextSelection;
        QValidator *_gameTextValidator;
        QVBoxLayout *_overallLayout;
        QHBoxLayout *_layout;
        QPushButton *_goFirstButton;
        QPushButton *_goPreviousButton;
        QPushButton *_goNextButton;
        QPushButton *_goLastButton;
        ChessBoard *_board;

        // Not to be released in the destructor, just borrowed
        PgnDatabase *_pgnDatabase;
        Game _currentBaseGame;

        void loadGameStart();
    };
};

#endif // GAMESELECTIONMAINZONE_H
