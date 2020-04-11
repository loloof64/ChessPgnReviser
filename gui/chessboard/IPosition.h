#ifndef IPOSITION_H
#define IPOSITION_H

#include <string>

namespace loloof64 {

    enum File {
        FILE_A,
        FILE_B,
        FILE_C,
        FILE_D,
        FILE_E,
        FILE_F,
        FILE_G,
        FILE_H
    };

    enum Rank {
        RANK_1,
        RANK_2,
        RANK_3,
        RANK_4,
        RANK_5,
        RANK_6,
        RANK_7,
        RANK_8
    };

    class UnimplementedException{};

    class IPosition {
    public:
        virtual ~IPosition(){}
        // Should return the position in Forsyth-Edwards Notation
        virtual std::string getFen() const { UnimplementedException ex; throw ex; }

        // Should return true for white turn, and false for black turn
        virtual bool isWhiteTurn() const { UnimplementedException ex; throw ex; }

        // Should return the piece value in Forsyth-Edwards Notation ('P' = white pawn, 'n' = black knight, ...)
        virtual char getPieceFenAt(int /*file*/ , int /*rank*/) const { UnimplementedException ex; throw ex; }

        // Should return true is, and only if, the given move is legal
        virtual bool isLegalMove(
                int /*startFile*/, int /*startRank*/, int /*endFile*/, int /*endRank*/) const
            { UnimplementedException ex; throw ex; }

        // Should make the given move if legal
        // promotionFen should be 'q' or 'Q' (either value whatever the side to move) for queen, 'r' or 'R' for rook,
        // 'b' or 'B' for bishop, or 'n' or 'N' for knight. Or the value 0 for leaving this field set to no_promotion.
        // Should return the new position in Forsyth-Edwards Notation, or throw an error if the move could not be applied
        // because it is illegal.
        virtual std::string makeMove(
                int /*startFile*/, int /*startRank*/, int /*endFile*/, int /*endRank*/, char /* promotionFen*/ = 0)
        { UnimplementedException ex; throw ex;}

        // Should tells whether the given move leads to a promotion, and return false if either no or move is illegal.
        virtual bool isPromotionMove(
                int /*startFile*/, int /*startRank*/, int /*endFile*/, int /*endRank*/) const
        { UnimplementedException ex; throw ex;}
    };
}

#endif // IPOSITION_H
