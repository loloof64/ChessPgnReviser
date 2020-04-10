#include "thcposition.h"

namespace loloof64 {

    ThcPosition::ThcPosition(std::string fen) : IPosition()
    {
        _position = thc::ChessPosition();
        auto success = _position.Forsyth(fen.c_str());
        if (!success) throw IllegalPosition();
    }

    std::string ThcPosition::getFen()
    {
        return _position.ForsythPublish();
    }

    bool ThcPosition::isWhiteTurn()
    {
        return _position.WhiteToPlay();
    }

    char ThcPosition::getPieceFenAt(int file, int rank)
    {
        if (file < 0 || file > 7) throw IllegalCoordinate(file, rank);
        if (rank < 0 || rank > 7) throw IllegalCoordinate(file, rank);

        auto squareIndex = 8*(7-rank) + file;
        return _position.squares[squareIndex];
    }

}
