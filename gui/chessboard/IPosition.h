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
        virtual ~IPosition(){};
        // Should return the position in Forsyth-Edwards Notation
        virtual std::string getFen() { UnimplementedException ex; throw ex; };

        // Should return true for white turn, and false for black turn
        virtual bool isWhiteTurn() { UnimplementedException ex; throw ex; };

        // Should return the piece value in Forsyth-Edwards Notation ('P' = white pawn, 'n' = black knight, ...)
        virtual char getPieceFenAt(int file , int rank) { UnimplementedException ex; throw ex; };
    };
}

#endif // IPOSITION_H
