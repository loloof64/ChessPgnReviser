#include "IPosition.h"

loloof64::IPosition::~IPosition()
{

}

QString loloof64::IPosition::pieceFenToPieceImageReference(char pieceFen)
{
    switch (pieceFen) {
        case 'P': return "pl.svg";
        case 'N': return "nl.svg";
        case 'B': return "bl.svg";
        case 'R': return "rl.svg";
        case 'Q': return "ql.svg";
        case 'K': return "kl.svg";

        case 'p': return "pd.svg";
        case 'n': return "nd.svg";
        case 'b': return "bd.svg";
        case 'r': return "rd.svg";
        case 'q': return "qd.svg";
        case 'k': return "kd.svg";

    default:
        return "";
    }
}
