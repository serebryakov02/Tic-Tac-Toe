#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gameconfigurationdialog.h"

namespace Ui {
class MainWindow;
}

struct Data {
    static constexpr int widthFactor = 50;
    static constexpr int boardSpacing = 1;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setGameOutcomeMsg(const QString &newGameOutcomeMsg);

private slots:
    void startNewGame();
    void boldCurrentPlayerName();
    void determineGameOutcomeMsg();

private:
    Ui::MainWindow *ui;

    GameConfigurationDialog *gameConfigurationDialog;
};

#endif // MAINWINDOW_H
