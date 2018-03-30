
#ifndef STERM_MAINWINDOW_HPP
#define STERM_MAINWINDOW_HPP

#include <memory>
#include <QMainWindow>
#include <ui_MainWindow.h>

namespace Ui {

class MainWindow;

}

class MainWindow : public QMainWindow
{
Q_OBJECT

private:
    std::unique_ptr<Ui::MainWindow> _ui;
    std::unique_ptr<QFont>          _defFont;

public:
    MainWindow();

public slots:
    void on_action_Exit_triggered();

};

#endif //STERM_MAINWINDOW_HPP
