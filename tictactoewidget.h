#ifndef TICTACTOEWIDGET_H
#define TICTACTOEWIDGET_H

#include <QWidget>
#include <QList>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class TicTacToeWidget; }
QT_END_NAMESPACE

struct MetaData {
    static constexpr int ROWS = 3;
    static constexpr int COLUMNS = 3;
    static constexpr const char* emptyStr = "";
};

enum Player {
    Player1, Player2
};

class TicTacToeWidget : public QWidget
{
    Q_OBJECT

public:
    TicTacToeWidget(QWidget *parent = nullptr);
    ~TicTacToeWidget();

    Player getPlayer() const;
    void setPlayer(Player newPlayer);

private slots:
    void handleClicksOnBoards(int);

private:
    Ui::TicTacToeWidget *ui;

    QList<QPushButton*> board;
    void createBoard();
    void clearBoard();

    Player player;
};
#endif // TICTACTOEWIDGET_H
