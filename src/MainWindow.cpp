/*
 * MIT License
 *
 * Copyright (c) 2018 Alexander Kotikov <alexandr.kotikov@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "MainWindow.hpp"

#include <QtWidgets>
#include <ui_MainWindow.h>

namespace sterm {
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
}
