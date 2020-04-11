#include "thcposition.h"

#include <QString>
#include <QVector>
#include <cctype>

#include <QMessageLogger>

namespace loloof64 {

    ThcPosition::ThcPosition(std::string fen) : IPosition()
    {
        _position = thc::ChessRules();
        auto success = _position.Forsyth(fen.c_str());
        if (!success) throw IllegalPositionException();
    }

    std::string ThcPosition::getFen() const
    {
        auto copy{_position};
        return copy.ForsythPublish();
    }

    bool ThcPosition::isWhiteTurn() const
    {
        return _position.WhiteToPlay();
    }

    char ThcPosition::getPieceFenAt(int file, int rank) const
    {
        if (file < 0 || file > 7) throw IllegalCoordinate(file, rank);
        if (rank < 0 || rank > 7) throw IllegalCoordinate(file, rank);

        auto squareIndex = 8*(7-rank) + file;
        return _position.squares[squareIndex];
    }

    bool ThcPosition::isLegalMove(int startFile, int startRank, int endFile, int endRank) const
    {
        QString moveStr;
        char startFileChar = 97 + startFile;
        char startRankChar = 49 + startRank;
        char endFileChar = 97 + endFile;
        char endRankChar = 49 + endRank;

        moveStr += startFileChar;
        moveStr += startRankChar;
        moveStr += endFileChar;
        moveStr += endRankChar;
        moveStr += 'q';

        thc::ChessRules copy{_position};
        thc::Move moveToTest;
        moveToTest.TerseIn(&copy, moveStr.toStdString().c_str());

        return moveToTest.NaturalOut(&copy) != std::string("--");
    }

    bool ThcPosition::isPromotionMove(int startFile, int startRank, int endFile, int endRank) const
    {
        QString moveStr;
        char startFileChar = 97 + startFile;
        char startRankChar = 49 + startRank;
        char endFileChar = 97 + endFile;
        char endRankChar = 49 + endRank;

        moveStr += startFileChar;
        moveStr += startRankChar;
        moveStr += endFileChar;
        moveStr += endRankChar;
        moveStr += 'q';

        thc::ChessRules copy{_position};
        thc::Move moveToTest;
        moveToTest.TerseIn(&copy, moveStr.toStdString().c_str());

        const auto isLegal = moveToTest.NaturalOut(&copy) != std::string("--");

        if (! isLegal) return false;

        const auto promotionsSpecials = QVector<thc::SPECIAL>{
            thc::SPECIAL::SPECIAL_PROMOTION_QUEEN,
            thc::SPECIAL::SPECIAL_PROMOTION_ROOK,
            thc::SPECIAL::SPECIAL_PROMOTION_BISHOP,
            thc::SPECIAL::SPECIAL_PROMOTION_KNIGHT
        };

        auto isPromotion = false;
        for (auto promotionToTest: promotionsSpecials)
        {
            if (moveToTest.special == promotionToTest) isPromotion = true;
        }

        return isPromotion;
    }

    std::string ThcPosition::makeMove(int startFile, int startRank, int endFile, int endRank, char promotionFen)
    {
        QString moveStr;
        char startFileChar = 97 + startFile;
        char startRankChar = 49 + startRank;
        char endFileChar = 97 + endFile;
        char endRankChar = 49 + endRank;

        moveStr += startFileChar;
        moveStr += startRankChar;
        moveStr += endFileChar;
        moveStr += endRankChar;
        moveStr += tolower(promotionFen);

        thc::ChessRules copy{_position};
        thc::Move moveToTest;
        moveToTest.TerseIn(&copy, moveStr.toStdString().c_str());

        const auto isLegal = moveToTest.NaturalOut(&copy) != std::string("--");

        if (! isLegal) throw new IllegalMoveException();
        copy.PlayMove(moveToTest);

        _position = copy;
        return copy.ForsythPublish();
    }
}
