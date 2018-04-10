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
#include <QStringList>

#include <fmt/format.h>

#include <ui_MainWindow.h>

#include "Version.hpp"
#include "Settings.hpp"
#include "SelectPortDialog.hpp"
#include "PlainTextTerminal.hpp"

namespace sterm
{
    MainWindow::MainWindow()
        : ui_{std::make_unique<Ui::MainWindow>()}
    {
        ui_->setupUi(this);
        term_ = std::make_unique<PlainTextTerminal>(*ui_->plainTextEdit); ///< Call after ui_->setupUi(this)!

        setWindowTitle(QString::fromStdString(Version::get().getAppNameAndVersion()));

        //TODO move to config file
        term_->setFont("Liberation Mono", 16);
        term_->setColorForeground(117, 231, 9); //117, 231, 9
        term_->setColorBackground(46, 52, 54); //46, 52, 54

        term_->printLineTm(fmt::format("*** {} ***", Version::get().getAppNameAndVersion()));
    }

    MainWindow::~MainWindow()
    {
        /// Workaround for std::unique_ptr<incomplete type> in hpp file.
    }

    void MainWindow::on_action_Open_triggered()
    {
        SelectPortDialog dlg(this);

        dlg.exec();

//        bool ok;
//        auto port = QInputDialog::getItem(this,
//                                          "Select port",
//                                          "Port",
//                                          Settings::get().getSystemPortList(),
//                                          0,
//                                          true,
//                                          &ok);
//
//        if (!ok)
//        {
//            return;
//        }
//
//        QMessageBox::information(this, nullptr, port);
    }

    void MainWindow::on_action_Exit_triggered()
    {
        QMessageBox::information(this, "Exit", "test");
        close();
    }
}
