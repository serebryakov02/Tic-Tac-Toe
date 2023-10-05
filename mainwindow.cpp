#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Styling the labels of the players name.
    ui->lblPlayer1->setFont(QFont("Times New Roman", 22));
    ui->lblPlayer1->setStyleSheet("QLabel {color:blue}");
    ui->lblPlayer2->setFont(QFont("Times New Roman", 22));
    ui->lblPlayer2->setStyleSheet("QLabel {color:red}");

    // Make sure that the name of the current player is bold.
    connect(ui->tictactoe, &TicTacToeWidget::changePlayer, this, &MainWindow::boldCurrentPlayerName);

    // Bold the name of the first player to play at the start.
    boldCurrentPlayerName();

    // Enabling of the actions.
    connect(ui->actionNewGame, &QAction::triggered, this, &MainWindow::startNewGame);
    connect(ui->actionQuitGame, &QAction::triggered, qApp, &QApplication::quit);

    gameConfigurationDialog = GameConfigurationDialog::getInstance();

    connect(ui->tictactoe, &TicTacToeWidget::finishGame, this, &MainWindow::determineGameOutcomeMsg);

    connect(this, &MainWindow::startAiMode, ui->tictactoe, &TicTacToeWidget::setAiMode);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::startNewGame
 * A method which manages the start of a new game.
 */
void MainWindow::startNewGame()
{
    // Reset the player names.
    ui->lblPlayer1->setText("");
    ui->lblPlayer2->setText("");

    // Reset the game side.
    gameConfigurationDialog->setGameSide(SideRange::minRange);

    // Clear configuration fields.
    gameConfigurationDialog->setPlayer1Name("");
    gameConfigurationDialog->setPlayer2Name("");

    // Reset some game configuration.
    gameConfigurationDialog->resetSomeConfig();

    // Reset the mode to the two-player mode in the Tic-Tac-Toe class.
    ui->tictactoe->setTwoPlayerMode();

    if (gameConfigurationDialog->exec() == QDialog::Rejected) {
        return;
    }

    // Check for AI mode.
    if (gameConfigurationDialog->getPlayer2Name() == SpecialData::aiName) {
        ui->tictactoe->resetContainers();
        emit startAiMode();
    }

    // Configuration of player names.
    ui->lblPlayer1->setText(gameConfigurationDialog->getPlayer1Name());
    ui->lblPlayer2->setText(gameConfigurationDialog->getPlayer2Name());

    int gameSide = gameConfigurationDialog->getGameSide();
    //auto mode = gameConfigurationDialog->getMode();

    // Adjustment of the Tic-Tac-Toe board size.
    ui->tictactoe->setFixedHeight(Data::widthFactor * (gameSide + Data::boardSpacing));
    ui->tictactoe->setFixedWidth(Data::widthFactor * (gameSide + Data::boardSpacing));

    // Hide the game title.
    ui->lblGameTitle->hide();
    // Update the side of the game.
    ui->tictactoe->setGameSide(gameSide);
    // Launch the game.
    ui->tictactoe->startOrRestartGame();
    // Enable the Tic-Tac-Toe board.
    ui->tictactoe->setEnabled(true);
}

/**
 * @brief MainWindow::boldCurrentPlayerName
 * A method which bolds the name of the current player.
 */
void MainWindow::boldCurrentPlayerName()
{
    // Bold the label of player1 if it is player1's turn.
    auto player1Font = ui->lblPlayer1->font();
    player1Font.setBold(ui->tictactoe->getCurrentPlayer() == Player::Player1);
    ui->lblPlayer1->setFont(player1Font);

    // Bold the label of player2 if it is player2's turn.
    auto player2Font = ui->lblPlayer2->font();
    player2Font.setBold(ui->tictactoe->getCurrentPlayer() == Player::Player2);
    ui->lblPlayer2->setFont(player2Font);
}

/**
 * @brief MainWindow::determineGameOutcomeMsg
 * A slot to determine the game outcome message.
 */
void MainWindow::determineGameOutcomeMsg()
{
    Winner winner = ui->tictactoe->getGameOutcome();
    if (winner == Winner::player1) {
        ui->tictactoe->setGameOutcomeMsg("The winner is " + ui->lblPlayer1->text());
    } else if (winner == Winner::player2) {
        ui->tictactoe->setGameOutcomeMsg("The winner is " + ui->lblPlayer2->text());
    } else if (winner == Winner::Draw) {
        ui->tictactoe->setGameOutcomeMsg("Draw Game");
    }
}
