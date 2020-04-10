#ifndef THCPOSITION_H
#define THCPOSITION_H

#include "../chessboard/IPosition.h"
#include "../../libs/thc-chess-library/ChessPosition.h"

namespace loloof64 {

    // Empty structure
    struct IllegalPosition {};

    // Structure with fields file and rank
    struct IllegalCoordinate{
        IllegalCoordinate(int file, int rank): file(file), rank(rank){};
        int file, rank;
    };

    class ThcPosition: public IPosition
    {
    public:
        // Takes an option string of the Forsyth-Edwards Notation of the position,
        // sets to standard if no given.
        ThcPosition(std::string fen="rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

        // Gets the Forsyth-Edwards Notation of the position
        std::string getFen() override;

        // True if white turn, false if black turn
        bool isWhiteTurn() override;

        // Gets the piece, in Forsyth-Edwards Notation, at the requested cell.
        // You can use the constants from File and Rank enumerations.
        // May throw IllegalCoordinates
        char getPieceFenAt(int file, int rank) override;
    private:
        thc::ChessPosition _position;
    };

}

#endif // THCPOSITION_H
