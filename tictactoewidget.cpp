#include "tictactoewidget.h"
#include "ui_tictactoewidget.h"
#include <QGridLayout>
#include <QSignalMapper>

TicTacToeWidget::TicTacToeWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TicTacToeWidget)
{
    ui->setupUi(this);

    player = Player::Player1;

    createBoard();
}

TicTacToeWidget::~TicTacToeWidget()
{
    delete ui;
}

/**
 * @brief TicTacToeWidget::clearBoard
 * A method which resets the board.
 */
void TicTacToeWidget::clearBoard()
{
    for (int i = 0; i < MetaData::ROWS * MetaData::COLUMNS; ++i) {
        board.at(i)->setText(MetaData::emptyStr);
    }
}

/**
 * @brief TicTacToeWidget::getPlayer
 * @return
 * A method which returns player.
 */
Player TicTacToeWidget::getPlayer() const
{
    return player;
}

/**
 * @brief TicTacToeWidget::setPlayer
 * @param newPlayer
 * A method which sets the player.
 */
void TicTacToeWidget::setPlayer(Player newPlayer)
{
    player = newPlayer;
}

/**
 * @brief TicTacToeWidget::handleClicksOnBoards
 * A slot to handle clicks on board.
 */
void TicTacToeWidget::handleClicksOnBoards(int buttonIndex)
{
    if (buttonIndex < 0 || buttonIndex >= board.size()) return;

    // The button which was clicked on.
    auto button = board.at(buttonIndex);
    // Styling of the button.
    button->setFont(QFont("Tahoma", 14, QFont::Bold));

    if (button->text() != MetaData::emptyStr) return;

    QString symbol;

    if (player == Player::Player1) {
        symbol = "X";
        button->setStyleSheet("QPushButton { color: blue; background: lightyellow }");
        button->setText(symbol);
        setPlayer(Player::Player2);
    } else {
        symbol = "O";
        button->setStyleSheet("QPushButton { color: red; background: lightgreen }");
        button->setText(symbol);
        setPlayer(Player::Player1);
    }
}

/**
 * @brief TicTacToeWidget::createBoard
 * A method which creates the board of the Tic-Tac-Toe game.
 */
void TicTacToeWidget::createBoard()
{
    auto gridLayout = new QGridLayout(this);
    auto signalMapper = new QSignalMapper(this);

    for (int row = 0; row < MetaData::ROWS; ++row) {
        for (int col = 0; col < MetaData::COLUMNS; ++col) {
            auto button = new QPushButton(this);
            button->setText(MetaData::emptyStr);
            button->setMinimumHeight(50);
            button->setMinimumWidth(50);

            signalMapper->setMapping(button, board.size());

            //connect(button, &QPushButton::clicked, signalMapper, &QSignalMapper::map);

            // Use a lambda function to connect the button's clicked signal to the QSignalMapper.
            connect(button, &QPushButton::clicked, [signalMapper, button]() {
                signalMapper->map(button);
            });
            connect(signalMapper, &QSignalMapper::mappedInt, this, &TicTacToeWidget::handleClicksOnBoards);

            gridLayout->addWidget(button, row, col);

            board.append(button);
        }
    }
}

