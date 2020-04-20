#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QMouseEvent>
#include "IPosition.h"

namespace loloof64 {
    struct DndData
    {
        explicit DndData(char pieceFen, int startFile, int startRank,
                         int pieceX, int pieceY):
            pieceFen(pieceFen), pointerInBounds(false), startFile(startFile), startRank(startRank),
            pieceX(pieceX), pieceY(pieceY){};
        DndData(const DndData&) = delete;
        DndData(const DndData&&) = delete;
        char pieceFen;
        bool pointerInBounds;
        int startFile, startRank;
        int endFile, endRank;
        int pieceX, pieceY;
    };

    enum class GameFinishedStatus
    {
        NOT_FINISHED,
        CHECKMATE,
        STALEMATE,
        FIFTY_MOVES_RULE,
        INSUFICIENT_MATERIAL,
        REPETITIONS,
        STOPPED,
    };

    enum class PlayerType
    {
        HUMAN, // player draw the moves with his mouse
        EXTERNAL, // player has to retranscript the move by calling playMove()
    };

    class ChessBoard : public QWidget
    {
        Q_OBJECT
    public:
        explicit ChessBoard(int cellsSize, QWidget *parent = nullptr);
        ~ChessBoard();
        inline bool gameInProgress(){ return _gameFinishedStatus == GameFinishedStatus::NOT_FINISHED; }
        inline bool isWhiteTurn(){ return _relatedPosition->isWhiteTurn(); }
        inline void setWhitePlayerType(PlayerType playerType) { _whitePlayer = playerType; };
        inline void setBlackPlayerType(PlayerType playerType) { _blackPlayer = playerType; };
        inline PlayerType getWhitePlayerType() const { return _whitePlayer; };
        inline PlayerType getBlackPlayerType() const { return _blackPlayer; };
        // Only effective if the current turn belongs to an external player
        // Returns true if, and only if, the move could be done.
        bool playMove(int startFile, int startRank, int endFile, int endRank, char promotionFen = 0);

    signals:
        // a move has been made
        // 1st parameter: the move san (QString)
        // 2nd parameter: the resulting position fen (QString)
        // 3rd parameter: the move coordinates (LastMoveCoordinates)
        // 4th parameter: true if the game is finished just after this move, false otherwise (bool)
        void moveDoneAsSan(QString, QString, LastMoveCoordinates, bool gameFinished);

        // a move has been made
        // 1st parameter: the move fan (QString)
        // 2nd parameter: the resulting position fen (QString)
        // 3rd parameter: the move coordinates (LastMoveCoordinates)
        // 4th parameter: true if the game is finished just after this move, false otherwise (bool)
        void moveDoneAsFan(QString, QString, LastMoveCoordinates, bool gameFinished);

        // Notify that is is the turn of an external player
        void externalTurn(QString currentPosition);

    public slots:
        void reverse();
        void newGame(QString startPosition);
        void stopGame();
        // Sets the requested position if the game is not in progress.
        // Simply ignoring the moveFan part of the given HistoryItem.
        // Returns true if and only if the move has been done.
        bool setPosition(const HistoryItem *);

    protected:
        void paintEvent(QPaintEvent *event) override;

    private:
        int _cellsSize;
        bool _reversed;
        GameFinishedStatus _gameFinishedStatus;
        IPosition *_relatedPosition;
        DndData *_dndData;
        LastMoveCoordinates *_lastMoveCoordinates;
        PlayerType _whitePlayer{PlayerType::HUMAN};
        PlayerType _blackPlayer{PlayerType::HUMAN};
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void emitExternalPlayerTurnIfNecessary();
        void updateLastMove(int startFile, int startRank, int endFile, int endRank);
        void handleGameFinished();
        void showGameFinishedMessageIfNecessary();
    };
}

#endif // CHESSBOARD_H
