#ifndef TICTACTOEWIDGET_H
#define TICTACTOEWIDGET_H

#include <QWidget>
#include <QList>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class TicTacToeWidget; }
QT_END_NAMESPACE

struct MetaData {
    //    static constexpr int ROWSCOLUMNS = 3;
    //    static constexpr int BOARDSIZE = ROWSCOLUMNS * ROWSCOLUMNS;
    static constexpr const char* emptyStr = "";
    static constexpr const char* player1Symbol = "X";
    static constexpr const char* player2Symbol = "O";
    static constexpr const char* player1Color = "blue";
    static constexpr const char* player2Color = "red";
    static constexpr const char* drawColor = "purple";
    static constexpr int freezeTime = 2000; // 2 secs.
    static constexpr int endOfGameWidth = 500;
    static constexpr int widthFactor = 50;
    static constexpr int boardSpacing = 1;
};

enum Player {
    Player1, Player2
};

enum Winner {
    player1, player2, Draw, NoWinnerYet
};

enum Mode {
    TwoPlayerMode, AIMode
};

class TicTacToeWidget : public QWidget
{
    Q_OBJECT

public:
    TicTacToeWidget(QWidget *parent = nullptr);
    ~TicTacToeWidget();

    Player getCurrentPlayer() const;
    void setPlayer(Player newPlayer);

    void setGameSide(int);

    Winner getGameOutcome() const;

    void setGameOutcomeMsg(const QString &newGameOutcomeMsg);

    void resetContainers();

signals:
    void finishGame();
    void changePlayer();
    // A signal which sends AI moves.
    void sendAiMoves(int);

private slots:
    void handleClicksOnBoards(int);
    void handleEndOfTheGame();

public slots:
    void startOrRestartGame();
    void setAiMode();

    // A slot to reset the two-player mode.
    void setTwoPlayerMode();

private:
    Ui::TicTacToeWidget *ui;

    QList<QPushButton*> board;
    void createBoard();
    void clearBoard();

    Player player;

    Winner winner;
    Winner determinePlayer(const QString&, int);

    // A variable to store the size of the Tic-Tac-Toe board game.
    int gameSide;

    // An attrubite to store the game outcome message.
    QString gameOutcomeMsg;

    Mode mode;

    // A containter to store player1 moves.
    QList<int> player1Moves;

    // A containter to store the moves of the AI opponent.
    QList<int> playerAIMoves;
};

#endif // TICTACTOEWIDGET_H
