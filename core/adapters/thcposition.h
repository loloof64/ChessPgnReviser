#ifndef THCPOSITION_H
#define THCPOSITION_H

#include "../IPosition.h"
#include "../../libs/thc-chess-library/ChessRules.h"
#include <QMap>
#include <QString>

namespace loloof64 {

    // Empty structure
    struct IllegalMoveException {};

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

        // Returns true is it is a legal position, false otherwise.
        bool isLegalPosition() const override;

        // Gets the Forsyth-Edwards Notation of the position
        std::string getFen() const override;

        // True if white turn, false if black turn
        bool isWhiteTurn() const override;

        // Gets the piece, in Forsyth-Edwards Notation, at the requested cell.
        // You can use the constants from File and Rank enumerations.
        // May throw IllegalCoordinates
        char getPieceFenAt(int file, int rank) const override;

        // True if the given move is legal
        // False otherwise
        bool isLegalMove(int startFile, int startRank, int endFile, int endRank) const override;

        // Tries to make the given move
        // Returns the new position in Forsyth-Edwards Notation if success, and throws an IllegalMoveException otherwise.
        // promotionFen should be 'q' or 'Q' (either value whatever the side to move) for queen, 'r' or 'R' for rook,
        // 'b' or 'B' for bishop, or 'n' or 'N' for knight.
        std::string makeMove(int startFile, int startRank, int endFile, int endRank, char promotionFen = 'q') override;


        // True if the given move leads to a promotion.
        // False if not or if it is an illegal move.
        bool isPromotionMove(int startFile, int startRank, int endFile, int endRank) const override;

        // True if it is checkmate, false otherwise.
        bool isCheckmate() const override;

        // True if it is stalemate, false otherwise.
        bool isStalemate() const override;

        // True if it is draw by the 50 moves rule, false otherwise.
        bool isFiftyMovesRuleDraw() const override;

        // True if it is draw by insufficient material, false otherwise.
        bool isInsuficientMaterialDraw() const override;

        // True if it is draw by 3-folds repetition, false otherwise.
        bool isThreeFoldRepetitionsDraw() const override;

        // Returns the given move Short Algebraic Notation on the current position.
        // Throws IllegalMoveException if the move is not legal.
        // promotionFen should be 'q' or 'Q' (either value whatever the side to move) for queen, 'r' or 'R' for rook,
        // 'b' or 'B' for bishop, or 'n' or 'N' for knight.
        QString getMoveSan(int, int, int, int, char = 0) const override;

        // Returns the given move Figurine Algebraic Notation on the current position.
        // Throws IllegalMoveException if the move is not legal.
        // promotionFen should be 'q' or 'Q' (either value whatever the side to move) for queen, 'r' or 'R' for rook,
        // 'b' or 'B' for bishop, or 'n' or 'N' for knight.
        QString getMoveFan(int, int, int, int, char = 0) const override;

    private:
        thc::ChessRules _position;
        QMap<QString, int> _recordedPositions;
    };

}

#endif // THCPOSITION_H
