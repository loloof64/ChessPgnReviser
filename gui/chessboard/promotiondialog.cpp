#include "promotiondialog.h"
#include <QString>

loloof64::PromotionDialog::PromotionDialog(QWidget *parent, bool whitePlayer, int imagesSize) :
    QDialog(parent, Qt::WindowTitleHint | Qt::CustomizeWindowHint)
{
    _mainLayout = new QHBoxLayout(this);
    _mainLayout->setSpacing(10);

    QString queenImageRef{
        whitePlayer ?
        ":/chess_vectors/ql.svg" :
        ":/chess_vectors/qd.svg"
    };
    QString rookImageRef{
        whitePlayer ?
        ":/chess_vectors/rl.svg" :
        ":/chess_vectors/rd.svg"
    };
    QString bishopImageRef{
        whitePlayer ?
        ":/chess_vectors/bl.svg" :
        ":/chess_vectors/bd.svg"
    };
    QString knightImageRef{
        whitePlayer ?
        ":/chess_vectors/nl.svg" :
        ":/chess_vectors/nd.svg"
    };

    _queenButton = new QPushButton(this);
    _rookButton = new QPushButton(this);
    _bishopButton = new QPushButton(this);
    _knightButton = new QPushButton(this);

    _queenButton->setIcon(QIcon(queenImageRef));
    _rookButton->setIcon(QIcon(rookImageRef));
    _bishopButton->setIcon(QIcon(bishopImageRef));
    _knightButton->setIcon(QIcon(knightImageRef));

    const auto iconsSize = QSize(imagesSize, imagesSize);
    _queenButton->setIconSize(iconsSize);
    _rookButton->setIconSize(iconsSize);
    _bishopButton->setIconSize(iconsSize);
    _knightButton->setIconSize(iconsSize);

    connect(_queenButton, &QPushButton::clicked, this, [this](){ emit validateQueenPromotion(); });
    connect(_rookButton, &QPushButton::clicked, this, [this](){ emit validateRookPromotion(); });
    connect(_bishopButton, &QPushButton::clicked, this, [this](){ emit validateBishopPromotion(); });
    connect(_knightButton, &QPushButton::clicked, this, [this](){ emit validateKnightPromotion(); });

    _mainLayout->addWidget(_queenButton);
    _mainLayout->addWidget(_rookButton);
    _mainLayout->addWidget(_bishopButton);
    _mainLayout->addWidget(_knightButton);

    setWindowTitle(tr("Select the promotion piece"));
    setModal(true);
}

loloof64::PromotionDialog::~PromotionDialog()
{
    delete _knightButton;
    delete _bishopButton;
    delete _rookButton;
    delete _queenButton;
    delete _mainLayout;
}
