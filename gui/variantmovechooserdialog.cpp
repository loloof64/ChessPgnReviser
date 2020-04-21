#include "variantmovechooserdialog.h"
#include <QListWidgetItem>

loloof64::VariantMoveChooserDialog::VariantMoveChooserDialog(QWidget *parent) : QDialog(parent)
{
    _mainLayout = new QVBoxLayout(this);
    _mainLayout->setSpacing(10);

    _mainMoveZone = new QListWidget(this);
    _variationsMovesZone = new QListWidget(this);

    _mainLayout->addWidget(_mainMoveZone);
    _mainLayout->addWidget(_variationsMovesZone);

    connect(_mainMoveZone, &QListWidget::itemClicked, this, [this](QListWidgetItem  * /*item*/)
    {
        emit mainMoveSelected();
    });


    connect(_variationsMovesZone, &QListWidget::itemClicked, this, [this](QListWidgetItem *item)
    {
        const auto moveIndex = _variationsMovesZone->row(item);
        emit variationSelected(moveIndex);
    });

    setLayout(_mainLayout);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    setModal(true);
}

loloof64::VariantMoveChooserDialog::~VariantMoveChooserDialog()
{
    delete _variationsMovesZone;
    delete _mainMoveZone;
    delete _mainLayout;
}

void loloof64::VariantMoveChooserDialog::setMainMove(QString mainMoveFan)
{
    _mainMoveZone->clear();
    _mainMoveZone->addItem(mainMoveFan);
}

void loloof64::VariantMoveChooserDialog::setVariationsMoves(QList<QString> variationsMovesFan)
{
    _variationsMovesZone->clear();
    for (auto variationData: variationsMovesFan)
    {
        _variationsMovesZone->addItem(variationData);
    }
}
