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
        resize(Settings::get().loadMainWindowSize());
        move(Settings::get().loadMainWindowPosition());
        setWindowState(Settings::get().loadMainWindowMaximizedState() ?
                       Qt::WindowMaximized :
                       Qt::WindowNoState);

        auto[fontName, pointSize, weight, italic] = Settings::get().loadTerminalFont();
        term_->setFont(fontName, pointSize, weight, italic);

        {
            auto[r, g, b, a] = Settings::get().loadColorBackground();
            term_->setColorBackground(r, g, b, a);
        }

        {
            auto[r, g, b, a] = Settings::get().loadColorForeground();
            term_->setColorForeground(r, g, b, a);
        }

        term_->printLineTm(fmt::format("*** {} [{}] ***",
                                       Version::get().getAppNameAndVersion(),
                                       Version::get().getBuildDate()));
    }

    MainWindow::~MainWindow()
    {
        Settings::get().saveMainWindowSize(size());
        Settings::get().saveMainWindowPosition(pos());
        Settings::get().saveMainWindowMaximizedState((windowState() & Qt::WindowMaximized) != 0);
    }

    void MainWindow::on_action_Open_triggered()
    {
        SelectPortDialog dlg(this);

        if (dlg.exec() == QDialog::Rejected)
        {
            return;
        }

        QMessageBox::information(this, nullptr, dlg.getPort());
    }

    void MainWindow::on_action_Exit_triggered()
    {
        QMessageBox::information(this, "Exit", "test");
        close();
    }
}
