#include "thcposition.h"

#include <QString>
#include <QVector>
#include <cctype>
#include <string>

#include <QMessageLogger>

namespace loloof64 {

    ThcPosition::ThcPosition(std::string fen) : IPosition()
    {
        _position = thc::ChessRules();
        _recordedPositions = QMap<std::string, int>();
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
        auto positionToRecord = _position.ForsythPublish();
        // Strip both moves count from the position
        auto previous = positionToRecord.find(" ");
        auto current = previous;
        for (auto partIndex = 0; partIndex < 4; partIndex++)
        {
            previous = current+1;
            current = positionToRecord.find(" ", previous);
        }
        positionToRecord = positionToRecord.substr(0, current-2);
        _recordedPositions[positionToRecord]++;

        return copy.ForsythPublish();
    }
}

bool loloof64::ThcPosition::isCheckmate() const
{
    thc::TERMINAL terminalStatus;
    auto copy = _position;
    copy.Evaluate(terminalStatus);

    return (terminalStatus == thc::TERMINAL::TERMINAL_WCHECKMATE)
            || (terminalStatus == thc::TERMINAL_BCHECKMATE);
}

bool loloof64::ThcPosition::isStalemate() const
{
    thc::TERMINAL terminalStatus;
    auto copy = _position;
    copy.Evaluate(terminalStatus);

    return (terminalStatus == thc::TERMINAL::TERMINAL_WSTALEMATE)
            || (terminalStatus == thc::TERMINAL_BSTALEMATE);
}

bool loloof64::ThcPosition::isFiftyMovesRuleDraw() const
{
    // Not relying on the ChessRules class implementation
    // because not well suited
    const auto fen = getFen();

    auto halfMovesCount{-1};
    auto previous = fen.find(" ");
    auto current = previous;
    for (auto partIndex = 0; partIndex < 4; partIndex++)
    {
        previous = current+1;
        current = fen.find(" ", previous);
    }

    auto halfMovesPart = fen.substr(previous, current);
    halfMovesCount = stoi(halfMovesPart);

    return halfMovesCount >= 50;
}

bool loloof64::ThcPosition::isInsuficientMaterialDraw() const
{
    // Not relying on the ChessRules class implementation
    // because not well suited
    // Also, here not testing the case K+B / K+B where the bishops are
    // on the same color.

    const auto whitePiecesToKeep = QVector<char>{'P', 'N', 'B', 'R', 'Q'};
    const auto blackPiecesToKeep = QVector<char>{'p', 'n', 'b', 'r', 'q'};

    QVector<char> whitePiecesExceptKing;
    QVector<char> blackPiecesExceptKing;

    for (auto rank = 0; rank < 8; rank++)
    {
        for (auto file = 0; file < 8; file++)
        {
            auto piece = getPieceFenAt(file, rank);
            if (whitePiecesToKeep.contains(piece)) whitePiecesExceptKing += piece;
            else if (blackPiecesToKeep.contains(piece)) blackPiecesExceptKing += piece;
        }
    }

    const auto loneKings = whitePiecesExceptKing.length() == 0 && blackPiecesExceptKing.length() == 0;
    if (loneKings) return true;

    const auto loneKnightOrBishop =
            (blackPiecesExceptKing.length() == 0 && whitePiecesExceptKing.length() == 1 && whitePiecesExceptKing[0] == 'N') ||
            (blackPiecesExceptKing.length() == 0 && whitePiecesExceptKing.length() == 1 && whitePiecesExceptKing[0] == 'B') ||
            (whitePiecesExceptKing.length() == 0 && blackPiecesExceptKing.length() == 1 && blackPiecesExceptKing[0] == 'n') ||
            (whitePiecesExceptKing.length() == 0 && blackPiecesExceptKing.length() == 1 && blackPiecesExceptKing[0] == 'b');
    if (loneKnightOrBishop) return true;

    return false;
}

bool loloof64::ThcPosition::isThreeFoldRepetitionsDraw() const
{
    // Not relying on the ChessRules class implementation
    // because not well suited

    auto positionCopy{_position};

    auto positionWithStrippedMoveCounts = positionCopy.ForsythPublish();
    auto previous = positionWithStrippedMoveCounts.find(" ");
    auto current = previous;
    for (auto partIndex = 0; partIndex < 4; partIndex++)
    {
        previous = current+1;
        current = positionWithStrippedMoveCounts.find(" ", previous);
    }
    positionWithStrippedMoveCounts = positionWithStrippedMoveCounts.substr(0, current-2);

    return _recordedPositions[positionWithStrippedMoveCounts] >= 3;
}

QString loloof64::ThcPosition::getMoveSan(int startFile, int startRank, int endFile, int endRank, char promotionFen) const
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

    const auto moveNotation = moveToTest.NaturalOut(&copy);
    const auto isLegal = moveNotation != std::string("--");

    if (! isLegal) throw new IllegalMoveException();
    return QString(moveNotation.c_str());
}

QString loloof64::ThcPosition::getMoveFan(int startFile, int startRank, int endFile, int endRank, char promotionFen) const
{
    const auto moveSan = getMoveSan(startFile, startRank, endFile, endRank, promotionFen);
    return moveSan;
}
