#include "tictactoewidget.h"
#include "gameconfigurationdialog.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    TicTacToeWidget w;
//    w.show();
//    auto test = GameConfigurationDialog::getInstance();
//    test->setPlayer1Name("Nikitos");
//    test->setPlayer2Name("Olya");
//    test->setGameSide(5);
//    test->show();
//    int ret = a.exec();
//    delete test;

    MainWindow mainWindow;
    mainWindow.show();

    return a.exec();
}
