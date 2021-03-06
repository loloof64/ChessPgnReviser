[![Build Status](https://travis-ci.com/loloof64/ChessPgnReviser.svg?branch=master)](https://travis-ci.com/loloof64/ChessPgnReviser)
[![Build Status](https://ci.appveyor.com/api/projects/status/github/loloof64/ChessPgnReviser?svg=true&branch=master)](https://ci.appveyor.com/project/loloof64/chesspgnreviser)

# Chess Pgn Reviser

Load your pgn and play try to remember the moves against the engine.
You select the types (human/computer) for both sides: then for each move
* if it is your turn, you have to guess either the main line or one of the variant
* if it is the computer turn, you will have to select the move if any variant, otherwise, computer will play the move automatically.

You should take care that each game of the pgn has at least a star as a result, and is not empty. Otherwise some game may be forgotten.


## Developers

This project has been made with QtCreator and Qt 5.14.

Don't forget to generate translations files, from resources/translations subfolder, with Qt Linguist.

## Credits

* FreeSerif font downloaded from https://fr.fonts2u.com/free-serif.police.
* Using some code from project [thc-chess-library](https://github.com/billforsternz/thc-chess-library).
* Using some code from project [chessx](http://chessx.sourceforge.net/).
* Chess pieces vectors have been downloaded from [Wikimedia Commons](https://commons.wikimedia.org/wiki/Category:SVG_chess_pieces).

### FlatIcon

Using some icon resources from [FlatIcon](https://www.flaticon.com/).

* swap svg by Good Ware
* start svg by SmashIcons
* stop svg by FreePik
* previous, next, left-arrow, right-arrow svg by Roundicons
* male svg by Pixelmeetup
* computer svg by Eucalyp
* chess png by Flat Icons (application icon)
