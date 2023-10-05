#include "tictactoewidget.h"
#include "ui_tictactoewidget.h"
#include <QGridLayout>
#include <QSignalMapper>
#include <QDebug>
#include <QTimer>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

TicTacToeWidget::TicTacToeWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TicTacToeWidget)
{
    ui->setupUi(this);

    player = Player::Player1;
    winner = Winner::NoWinnerYet;
    mode = Mode::TwoPlayerMode;

    // Connection of the transmitted AI moves to the function which
    // handles moves on the Tic-Tac-Toe board.
    connect(this, &TicTacToeWidget::sendAiMoves, this, &TicTacToeWidget::handleClicksOnBoards);
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
    for (int i = 0; i < gameSide * gameSide; ++i) {
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
    int rowNumber = buttonIndex / gameSide;
    int colNumber = buttonIndex % gameSide;

    int counter = 0;

    // Horizontal check: forward check.
    int newColumn = colNumber;
    bool validateSecondCheck = true;
    while (++newColumn < gameSide) {
        // Position of the next button in the board.
        int newPosition = rowNumber * gameSide + newColumn;

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
        int newPosition = rowNumber * gameSide + newColumn;
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
    if (++counter == gameSide) {
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
        int newPosition = newRow * gameSide + newColumn;

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
    while (++newRow < gameSide && validateSecondCheck) {
        int newPosition = newRow * gameSide + newColumn;

        auto button = board.at(newPosition);
        if (button->text() != symbol) {
            break;
        } else {
            counter++;
        }
    }

    // Did the player win vertically?
    if (++counter == gameSide) {
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
        int newPosition = newRow * gameSide + newColumn;

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
    while (++newRow < gameSide && ++newColumn < gameSide && validateSecondCheck) {
        int newPosition = newRow * gameSide + newColumn;

        auto button = board.at(newPosition);
        if (button->text() != symbol) {
            break;
        } else {
            counter++;
        }
    }

    // Did the player win diagonally? (backslash)
    if (++counter == gameSide) {
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
    while (--newRow >= 0 && ++newColumn < gameSide) {
        int newPosition = newRow * gameSide + newColumn;

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
    while (++newRow < gameSide && --newColumn >= 0 && validateSecondCheck) {
        int newPosition = newRow * gameSide + newColumn;

        auto button = board.at(newPosition);
        if (button->text() != symbol) {
            break;
        } else {
            counter++;
        }
    }

    // Did the player win diagonally? (forward slash)
    if (++counter == gameSide) {
        if (symbol == MetaData::player1Symbol) {
            return Winner::player1;
        } else if (symbol == MetaData::player2Symbol) {
            return Winner::player2;
        }
    }

    // Check for the draw
    for (int i = 0; i < gameSide * gameSide; ++i) {
        if (board.at(i)->text() == MetaData::emptyStr) {
            return Winner::NoWinnerYet;
        }
    }

    return Winner::Draw;
}

/**
 * @brief TicTacToeWidget::setGameOutcomeMsg
 * @param newGameOutcomeMsg
 * A method to set the game outcome message.
 */
void TicTacToeWidget::setGameOutcomeMsg(const QString &newGameOutcomeMsg)
{
    gameOutcomeMsg = newGameOutcomeMsg;
}

/**
 * @brief TicTacToeWidget::resetContainers
 * A method to reset containers.
 */
void TicTacToeWidget::resetContainers()
{
    player1Moves.clear();
    playerAIMoves.clear();
}

/**
 * @brief TicTacToeWidget::getPlayer
 * @return
 * A method which returns player.
 */
Player TicTacToeWidget::getCurrentPlayer() const
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
 * @brief TicTacToeWidget::setGameSide
 * A method to set the side of the game.
 */
void TicTacToeWidget::setGameSide(int gs)
{
    gameSide = gs;
}

/**
 * @brief TicTacToeWidget::getWinner
 * @return
 * A method to return the game outcome.
 */
Winner TicTacToeWidget::getGameOutcome() const
{
    return winner;
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
        button->setStyleSheet(QString("QPushButton { color:") + MetaData::player1Color
                              + "; background: lightyellow }");
        button->setText(symbol);
        button->setDisabled(true);
    } else {
        symbol = MetaData::player2Symbol;
        button->setStyleSheet(QString("QPushButton { color: ") + MetaData::player2Color
                              + "; background: lightgreen }");
        button->setText(symbol);
        button->setDisabled(true);
    }

    // Determine the winner.
    winner = determinePlayer(symbol, buttonIndex);
    if (winner == Winner::NoWinnerYet) {
        if (player == Player::Player1) {
            setPlayer(Player::Player2);
            emit changePlayer();
        }
        else if (player == Player::Player2) {
            setPlayer(Player::Player1);
            emit changePlayer();
        }
    } else {
        this->setDisabled(true);
        QTimer::singleShot(MetaData::freezeTime, this, &TicTacToeWidget::finishGame);
        connect(this, &TicTacToeWidget::finishGame, this, &TicTacToeWidget::handleEndOfTheGame);
    }
}

/**
 * @brief TicTacToeWidget::handleEndOfTheGame
 * A slot to handle the end of the game.
 */
void TicTacToeWidget::handleEndOfTheGame()
{
    // Emptying of the Tic-tac-Tow window.
    // Retrieve layout.
    auto layout = this->layout();

    // Placeholder layout item.
    QLayoutItem *layoutItem;
    // Retrieve the layout items, delete their widgets
    // and then delete the layout items.
    while (layout != nullptr && (layoutItem = layout->takeAt(0)) != nullptr) {
        delete layoutItem->widget();
        delete layoutItem;
    }
    // Delete the layout.
    delete layout;

    // Clear the board.
    board.clear();

    // Creation of the layout for the window to display the outcome of the game.
    auto vLayout = new QVBoxLayout(this);
    vLayout->setAlignment(Qt::AlignCenter);

    auto restartLbl = new QLabel(this);
    auto restartBtn = new QPushButton("Restart", this);
    QString restartLblColor;
    QString restartBtnColor;
    if (winner == Winner::player1) {
        restartLblColor = QString("QLabel { color: ") + MetaData::player1Color + ";}";
        restartBtnColor = QString("QPushButton { color: ") + MetaData::player1Color + ";}";
    } else if (winner == Winner::player2) {
        restartLblColor = QString("QLabel { color: ") + MetaData::player2Color + ";}";
        restartBtnColor = QString("QPushButton { color: ") + MetaData::player2Color + ";}";
    } else if (winner == Winner::Draw) {
        restartLblColor = QString("QLabel { color: ") + MetaData::drawColor + ";}";
        restartBtnColor = QString("QPushButton { color: ") + MetaData::drawColor + ";}";
    }

    // Style the button.
    restartBtn->setMinimumWidth(100);
    restartBtn->setMinimumHeight(40);
    restartBtn->setFont(QFont("Liberation Serif", 14, QFont::Bold));
    restartBtn->setStyleSheet(restartBtnColor);
    // Style the label.
    restartLbl->setFont(QFont("Liberation Serif", 14, QFont::Bold));
    restartLbl->setAlignment(Qt::AlignCenter);
    restartLbl->setStyleSheet(restartLblColor);
    restartLbl->setText(gameOutcomeMsg);
    // Adjust the size of the Tic-Tac-Toe board for full display of long names.
    this->setMaximumWidth(MetaData::endOfGameWidth);

    vLayout->addWidget(restartLbl);
    vLayout->addWidget(restartBtn);

    // Enable the Tic-Tac-Toe window.
    this->setEnabled(true);

    connect(restartBtn, &QPushButton::clicked, this, &TicTacToeWidget::startOrRestartGame);
}

void TicTacToeWidget::triggerAiMoveCalculation()
{

}

/**
 * @brief TicTacToeWidget::restartGame
 * A method to manage restart the game.
 */
void TicTacToeWidget::startOrRestartGame()
{
    // Reset the width of the gameboard.
    this->setFixedWidth(MetaData::widthFactor * (gameSide + MetaData::boardSpacing));

    // Set the first player to start playing.
    player = Player::Player1;

    emit changePlayer();

    // Reset the containers if it is the AI mode.
    if (mode == Mode::AIMode) resetContainers();

    // Empty the Tic-Tac-Toe board if neccesary.
    auto layout = this->layout();
    QLayoutItem *layoutItem;
    while (layout != nullptr && (layoutItem = layout->takeAt(0)) != nullptr) {
        delete layoutItem->widget();
        delete layoutItem;
    }
    delete layout;
    board.clear();

    // Create a new board.
    createBoard();

    this->setEnabled(true);
}

/**
 * @brief TicTacToeWidget::startAiMode
 * A slot to set the AI mode.
 */
void TicTacToeWidget::setAiMode()
{
    mode = Mode::AIMode;
}

/**
 * @brief TicTacToeWidget::setTwoPlayerMode
 */
void TicTacToeWidget::setTwoPlayerMode()
{
    mode = Mode::TwoPlayerMode;
}

/**
 * @brief TicTacToeWidget::createBoard
 * A method which creates the board of the Tic-Tac-Toe game.
 */
void TicTacToeWidget::createBoard()
{
    auto gridLayout = new QGridLayout(this);
    auto signalMapper = new QSignalMapper(this);

    for (int row = 0; row < gameSide; ++row) {
        for (int col = 0; col < gameSide; ++col) {
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

