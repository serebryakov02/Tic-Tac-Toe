#include "tictactoewidget.h"
#include "ui_tictactoewidget.h"
#include <QGridLayout>
#include <QSignalMapper>
#include <QDebug>

TicTacToeWidget::TicTacToeWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TicTacToeWidget)
{
    ui->setupUi(this);

    player = Player::Player1;

    createBoard();

    resize(218, 182);
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
 * A method which determines the winner of the game.
 * @brief TicTacToeWidget::determinePlayer
 * @return
 */
Winner TicTacToeWidget::determinePlayer(const QString &symbol, int buttonIndex)
{
    // Step 1: get the row number and column number
    // of the clicked button in the grid.
    int rowNumber = buttonIndex / MetaData::COLUMNS;
    int colNumber = buttonIndex % MetaData::COLUMNS;

    int counter = 0;

    // Horizontal check: forward check.
    int newColumn = colNumber;
    bool validateSecondCheck = true;
    while (++newColumn < MetaData::COLUMNS) {
        // Position of the next button in the board.
        int newPosition = rowNumber * MetaData::COLUMNS + newColumn;

        // Retrieve next button.
        auto button = board.at(newPosition);
        // Check if the next button does not have the desired symbol.
        if (button->text() != symbol) {
            validateSecondCheck = false;
            break;
        } else {
            counter++;
        }
    }

    // Horizontal check: backward check.
    newColumn = colNumber;
    while (validateSecondCheck && --newColumn >= 0) {
        // Position of the next button in the board.
        int newPosition = rowNumber * MetaData::COLUMNS + newColumn;
        // Retrieve next button.
        auto button = board.at(newPosition);
        // Check if the next button does not have the desired symbol.
        if (button->text() != symbol) {
            break;
        } else {
            counter++;
        }
    }

    // Did the player win horizontally?
    if (++counter == MetaData::COLUMNS) {
        if (symbol == MetaData::player1Symbol) {
            return Winner::player1;
        } else if (symbol == MetaData::player2Symbol) {
            return Winner::player2;
        }
    }

    return Winner::NoWinnerYet;
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
        symbol = MetaData::player1Symbol;
        button->setStyleSheet("QPushButton { color: blue; background: lightyellow }");
        button->setText(symbol);
        button->setDisabled(true);
        //setPlayer(Player::Player2);
    } else {
        symbol = MetaData::player2Symbol;
        button->setStyleSheet("QPushButton { color: red; background: lightgreen }");
        button->setText(symbol);
        button->setDisabled(true);
        //setPlayer(Player::Player1);
    }

    // Determine the winner.
    auto winner = determinePlayer(symbol, buttonIndex);
    if (winner == Winner::NoWinnerYet) {
        if (player == Player::Player1) {
            setPlayer(Player::Player2);
        }
        else if (player == Player::Player2) {
            setPlayer(Player::Player1);
        }
    } else if (winner == Winner::player1) {
        // Disabling the board.
        this->setDisabled(true);
        qDebug() << "Player 1 wins!";
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

