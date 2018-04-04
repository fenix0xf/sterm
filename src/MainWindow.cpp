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

#include <QMainWindow>
#include <QMessageBox>
#include <QInputDialog>

#include <fmt/format.h>
#include <ui_MainWindow.h>

#include <PlainTextTerminal.hpp>
#include <Version.hpp>

namespace sterm
{
    MainWindow::MainWindow()
        : ui_{std::make_unique<Ui::MainWindow>()}
    {
        ui_->setupUi(this);
        term_ = std::make_unique<PlainTextTerminal>(*ui_->plainTextEdit); ///< Call after ui_->setupUi(this)!

        setWindowTitle(QString::fromStdString(Version::get().getAppNameAndVersion()));

        //TODO move to config file
        term_->setFont("Liberation Mono", 24);
        term_->setColorForeground(0, 255, 0);
        term_->setColorBackground(0, 0, 0);

        term_->printLineTm(fmt::format("*** {} ***", Version::get().getAppNameAndVersion()));
    }

    MainWindow::~MainWindow()
    {
        /// Workaround for std::unique_ptr<incomplete type> in hpp file.
    }

    void MainWindow::on_action_Open_triggered()
    {
        QStringList list;
        list.append("/dev/ttyUSB-RS485"); //TODO move to config file

        bool ok;
        auto port = QInputDialog::getItem(this, "Select port", "Port", list, 0, true, &ok);

        if (!ok)
        {
            return;
        }

        QMessageBox::information(this, nullptr, port);
    }

    void MainWindow::on_action_Exit_triggered()
    {
        QMessageBox::information(this, "Exit", "test");
        close();
    }
}
