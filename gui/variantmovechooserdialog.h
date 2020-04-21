#ifndef VARIANTMOVECHOOSERDIALOG_H
#define VARIANTMOVECHOOSERDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QListWidget>
#include <QList>
#include <QFrame>

namespace loloof64 {
    class VariantMoveChooserDialog : public QDialog
    {
        Q_OBJECT
    public:
        explicit VariantMoveChooserDialog(QWidget *parent = nullptr);
        ~VariantMoveChooserDialog();

        void setMainMove(QString mainMoveFan);
        void setVariationsMoves(QList<QString> variationsMovesFan);
    signals:
        void variationSelected(int index);
        void mainMoveSelected();
    private:
        QVBoxLayout *_mainLayout;
        QListWidget *_mainMoveZone;
        QListWidget *_variationsMovesZone;
    };
};

#endif // VARIANTMOVECHOOSERDIALOG_H
