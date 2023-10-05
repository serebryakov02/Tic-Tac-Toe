#include "gameconfigurationdialog.h"
#include "ui_gameconfigurationdialog.h"
#include <QPushButton>
#include <QDebug>

GameConfigurationDialog::GameConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameConfigurationDialog)
{
    ui->setupUi(this);

    // Make sure that the Ok button is disabled at the start.
    updateOkBtn();

    ui->spinBox->setRange(SideRange::minRange, SideRange::maxRange);
    ui->horizontalSlider->setRange(SideRange::minRange, SideRange::maxRange);

    ui->radioTwoPlayerMode->setChecked(true);
}

GameConfigurationDialog::~GameConfigurationDialog()
{
    delete ui;
}

/**
 * @brief GameConfigurationDialog::setPlayer1Name
 * @param name
 * A method to set the name of player 1.
 */
void GameConfigurationDialog::setPlayer1Name(const QString &name) const
{
    ui->txtPlayer1->setText(name);
}

/**
 * @brief GameConfigurationDialog::setPlayer2Name
 * @param name
 * A method to set the name of player 2.
 */
void GameConfigurationDialog::setPlayer2Name(const QString &name) const
{
    ui->txtPlayer2->setText(name);
}

/**
 * @brief GameConfigurationDialog::getPlayer1Name
 * @return
 * A method to return player 1's name
 */
QString GameConfigurationDialog::getPlayer1Name() const
{
    return ui->txtPlayer1->text();
}

/**
 * @brief GameConfigurationDialog::getPlayer2Name
 * @return
 * A method to return player 1's name
 */
QString GameConfigurationDialog::getPlayer2Name() const
{
    return ui->txtPlayer2->text();
}

/**
 * @brief GameConfigurationDialog::setGameSide
 * @param side
 * A method to set the size of the game side.
 */
void GameConfigurationDialog::setGameSide(int side) const
{
    if (side < SideRange::minRange || side > SideRange::maxRange) return;
    ui->spinBox->setValue(side);
    ui->horizontalSlider->setValue(side);
}

/**
 * @brief GameConfigurationDialog::getGameSide
 * @return
 * A method to get the game side value.
 */
int GameConfigurationDialog::getGameSide() const
{
    return ui->spinBox->value();
}

/**
 * @brief GameConfigurationDialog::getMode
 * @return
 * Method for returning selected mode.
 */
//Mode GameConfigurationDialog::getMode() const
//{
//    if (ui->radioTwoPlayerMode->isChecked()) {
//        return Mode::TwoPlayer;
//    } else if (ui->radioAIMode->isChecked()) {
//        return Mode::AI;
//    }
//}

// Initialization of the static member.
GameConfigurationDialog* GameConfigurationDialog::gameConfigurationDialog = nullptr;

/**
 * @brief GameConfigurationDialog::getInstance
 * @return GameConfigurationDialog *
 * Returns the unique instance of class created once.
 */
GameConfigurationDialog *GameConfigurationDialog::getInstance()
{
    if (gameConfigurationDialog == nullptr) {
        gameConfigurationDialog = new GameConfigurationDialog;
    }
    return gameConfigurationDialog;
}

/**
 * @brief GameConfigurationDialog::resetSomeConfig
 * A method to reset some configurations.
 */
void GameConfigurationDialog::resetSomeConfig()
{
    ui->radioTwoPlayerMode->setChecked(true);
    ui->txtPlayer2->setEnabled(true);
    ui->txtPlayer2->setText("");
}

/**
 * @brief GameConfigurationDialog::updateOkBtn
 * A method to update Ok button of the configuration window
 */
void GameConfigurationDialog::updateOkBtn()
{
    bool player1NameEnetered = ui->txtPlayer1->text().isEmpty();
    bool player2NameEntered = ui->txtPlayer2->text().isEmpty();
    auto button = ui->buttonBox->button(QDialogButtonBox::Ok);
    button->setDisabled(player1NameEnetered || player2NameEntered);
}

/**
 * @brief GameConfigurationDialog::on_buttonBox_clicked
 * @param button
 * A slot to handle clicks on the button box of the comfiguration window.
 */
void GameConfigurationDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    if (button == ui->buttonBox->button(QDialogButtonBox::Ok)) {
        if (ui->radioTwoPlayerMode->isChecked()) {
            qDebug() << "Two Players Mode";
        } else if (ui->radioAIMode->isChecked()) {
            qDebug() << "AI Mode";
        }
    }
}

void GameConfigurationDialog::on_radioAIMode_clicked()
{
    ui->txtPlayer2->setText(SpecialData::aiName);
    ui->txtPlayer2->setDisabled(true);
}

void GameConfigurationDialog::on_radioTwoPlayerMode_clicked()
{
    if (ui->txtPlayer2->text() == SpecialData::aiName) {
        ui->txtPlayer2->setText("");
        ui->txtPlayer2->setDisabled(false);
    }
}
