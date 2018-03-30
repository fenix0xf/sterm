
#include <QtWidgets>
#include <ui_MainWindow.h>

#include "MainWindow.hpp"

MainWindow::MainWindow()
{
    Ui::MainWindow ui{};
    ui.setupUi(this);

    QObject::connect(ui.action_Exit, SIGNAL(triggered()), this, SLOT(closeApp()));
}

void MainWindow::closeApp()
{
//    QMessageBox::information(this, "Exit", "test");
    close();
}
