#ifndef MOVESHISTORYBUTTONS_H
#define MOVESHISTORYBUTTONS_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

namespace loloof64 {
    class MovesHistoryButtons : public QWidget
    {
        Q_OBJECT
    public:
        explicit MovesHistoryButtons(QWidget *parent = nullptr);
        ~MovesHistoryButtons();

    signals:
        void requestFirstPosition();
        void requestLastPosition();
        void requestPreviousPosition();
        void requestNextPosition();

    private:
        QHBoxLayout *_mainLayout;
        QPushButton *_gotoStartButton;
        QPushButton *_gotoPreviousButton;
        QPushButton *_gotoNextButton;
        QPushButton *_gotoEndButton;
    };
}

#endif // MOVESHISTORYBUTTONS_H
