#ifndef GAMECONFIGURATIONDIALOG_H
#define GAMECONFIGURATIONDIALOG_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class GameConfigurationDialog;
}

struct SideRange {
    static constexpr int minRange = 3;
    static constexpr int maxRange = 10;
};

//enum Mode {
//    TwoPlayer, AI
//};

struct SpecialData {
    static constexpr const char* aiName = "Mister AI";
};

class GameConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    ~GameConfigurationDialog();

    // Setters for player names.
    void setPlayer1Name(const QString& name) const;
    void setPlayer2Name(const QString& name) const;

    // Getters for player names.
    QString getPlayer1Name() const;
    QString getPlayer2Name() const;

    // Setters and getters for the game side.
    void setGameSide(int side) const;
    int getGameSide() const;

    // Method for returning selected mode.
    //Mode getMode() const;

    // Singleton function.
    static GameConfigurationDialog* getInstance();

    // A method to reset some configurations.
    void resetSomeConfig();

public slots:
    void updateOkBtn();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_radioAIMode_clicked();

    void on_radioTwoPlayerMode_clicked();

private:
    Ui::GameConfigurationDialog *ui;

    // Impossible to create instances of the class.
    explicit GameConfigurationDialog(QWidget *parent = nullptr);

    static GameConfigurationDialog *gameConfigurationDialog;
};

#endif // GAMECONFIGURATIONDIALOG_H
