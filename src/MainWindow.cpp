
#include <QtWidgets>
#include <ui_MainWindow.h>

#include "MainWindow.hpp"

MainWindow::MainWindow() :
    _ui{std::make_unique<Ui::MainWindow>()},
    _defFont{std::make_unique<QFont>("Liberation Mono", 12)}
{
    _ui->setupUi(this);
    _ui->plainTextEdit->setFont(*_defFont);

    auto palette = _ui->plainTextEdit->palette();
    palette.setColor(QPalette::Base, Qt::black);
    palette.setColor(QPalette::Text, Qt::green);
    _ui->plainTextEdit->setPalette(palette);

    _ui->plainTextEdit->setPlainText("qweqweqwe\nqweqweqwe1\nwwww");

    _ui->plainTextEdit->appendPlainText("11111");
    _ui->plainTextEdit->appendPlainText("22222");

    const auto& tm = QTime::currentTime();

    _ui->plainTextEdit->appendPlainText(QString("%1: data").arg(tm.toString(Qt::ISODateWithMs)));
}

void MainWindow::on_action_Exit_triggered()
{
    QMessageBox::information(this, "Exit", "test");
    close();
}
