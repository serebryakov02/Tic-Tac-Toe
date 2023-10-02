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
    for (int i = 0; i < MetaData::ROWSCOLUMNS * MetaData::ROWSCOLUMNS; ++i) {
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
    int rowNumber = buttonIndex / MetaData::ROWSCOLUMNS;
    int colNumber = buttonIndex % MetaData::ROWSCOLUMNS;

    int counter = 0;

    // Horizontal check: forward check.
    int newColumn = colNumber;
    bool validateSecondCheck = true;
    while (++newColumn < MetaData::ROWSCOLUMNS) {
        // Position of the next button in the board.
        int newPosition = rowNumber * MetaData::ROWSCOLUMNS + newColumn;

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
        int newPosition = rowNumber * MetaData::ROWSCOLUMNS + newColumn;
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
    if (++counter == MetaData::ROWSCOLUMNS) {
        if (symbol == MetaData::player1Symbol) {
            return Winner::player1;
        } else if (symbol == MetaData::player2Symbol) {
            return Winner::player2;
        }
    }

    // Vertical check: upward and downward.
    counter = 0;
    validateSecondCheck = false;
    int newRow = rowNumber;
    // Upward check.
    while (--newRow >= 0) {
        // Get the position index of the next position
        // in the upward direction.
        int newPosition = newRow * MetaData::ROWSCOLUMNS + newColumn;

        auto button = board.at(newPosition);
        if (button->text() != symbol) {
            validateSecondCheck = false;
            break;
        } else {
            counter++;
        }
    }

    // Downward check.
    newRow = rowNumber;
    while (++newRow < MetaData::ROWSCOLUMNS && validateSecondCheck) {
        int newPosition = newRow * MetaData::ROWSCOLUMNS + newColumn;

        auto button = board.at(newPosition);
        if (button->text() != symbol) {
            break;
        } else {
            counter++;
        }
    }

    // Did the player win vertically?
    if (++counter == MetaData::ROWSCOLUMNS) {
        if (symbol == MetaData::player1Symbol) {
            return Winner::player1;
        } else if (symbol == MetaData::player2Symbol) {
            return Winner::player2;
        }
    }

    // Backslash diagonal check.
    // Upward direction.
    counter = 0;
    validateSecondCheck = true;

    newRow = rowNumber;
    newColumn = colNumber;
    while(--newRow >= 0 && --newColumn >= 0) {
        int newPosition = newRow * MetaData::ROWSCOLUMNS + newColumn;

        auto button = board.at(newPosition);
        if (button->text() != symbol) {
            validateSecondCheck = false;
            break;
        } else {
            counter++;
        }
    }

    // Downward direction.
    newRow = rowNumber;
    newColumn = colNumber;
    while (++newRow < MetaData::ROWSCOLUMNS && ++newColumn < MetaData::ROWSCOLUMNS && validateSecondCheck) {
        int newPosition = newRow * MetaData::ROWSCOLUMNS + newColumn;

        auto button = board.at(newPosition);
        if (button->text() != symbol) {
            break;
        } else {
            counter++;
        }
    }

    // Did the player win diagonally? (backslash)
    if (++counter == MetaData::ROWSCOLUMNS) {
        if (symbol == MetaData::player1Symbol) {
            return Winner::player1;
        } else if (symbol == MetaData::player2Symbol) {
            return Winner::player2;
        }
    }

    // Forward slash diagonal check.
    // Upward direction.
    counter = 0;
    validateSecondCheck = true;

    newRow = rowNumber;
    newColumn = colNumber;
    while (--newRow >= 0 && ++newColumn < MetaData::ROWSCOLUMNS) {
        int newPosition = newRow * MetaData::ROWSCOLUMNS + newColumn;

        auto button = board.at(newPosition);
        if (button->text() != symbol) {
            validateSecondCheck = false;
            break;
        } else {
            counter++;
        }
    }

    // Downward direction.
    newRow = rowNumber;
    newColumn = colNumber;
    while (++newRow < MetaData::ROWSCOLUMNS && --newColumn >= 0 && validateSecondCheck) {
        int newPosition = newRow * MetaData::ROWSCOLUMNS + newColumn;

        auto button = board.at(newPosition);
        if (button->text() != symbol) {
            break;
        } else {
            counter++;
        }
    }

    // Did the player win diagonally? (forward slash)
    if (++counter == MetaData::ROWSCOLUMNS) {
        if (symbol == MetaData::player1Symbol) {
            return Winner::player1;
        } else if (symbol == MetaData::player2Symbol) {
            return Winner::player2;
        }
    }

    // Check for the draw
    for (int i = 0; i < MetaData::BOARDSIZE; ++i) {
        if (board.at(i)->text() == MetaData::emptyStr) {
            return Winner::NoWinnerYet;
        }
    }

    return Winner::Draw;
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
    } else {
        symbol = MetaData::player2Symbol;
        button->setStyleSheet("QPushButton { color: red; background: lightgreen }");
        button->setText(symbol);
        button->setDisabled(true);
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
    } else if (winner == Winner::player2) {
        this->setDisabled(true);
        qDebug() << "Player 2 wins!";
    } else if (winner == Winner::Draw) {
        this->setDisabled(true);
        qDebug() << "Draw!";
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

    for (int row = 0; row < MetaData::ROWSCOLUMNS; ++row) {
        for (int col = 0; col < MetaData::ROWSCOLUMNS; ++col) {
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

