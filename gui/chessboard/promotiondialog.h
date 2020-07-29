#ifndef PROMOTIONDIALOG_H
#define PROMOTIONDIALOG_H

#include <QDialog>
#include <QHBoxLayout>
#include <QPushButton>

namespace loloof64
{
    class PromotionDialog : public QDialog
    {
        Q_OBJECT
    public:
        explicit PromotionDialog(QWidget *parent = nullptr, bool whitePlayer = true, int imagesSize = 45);
        ~PromotionDialog();
    signals:
        void validateQueenPromotion();
        void validateRookPromotion();
        void validateBishopPromotion();
        void validateKnightPromotion();

    private:
        QHBoxLayout *_mainLayout;
        QPushButton *_queenButton;
        QPushButton *_rookButton;
        QPushButton *_bishopButton;
        QPushButton *_knightButton;
    };
};

#endif // PROMOTIONDIALOG_H
