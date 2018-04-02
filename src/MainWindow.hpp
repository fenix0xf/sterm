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

#ifndef STERM_MAINWINDOW_HPP
#define STERM_MAINWINDOW_HPP

#include <memory>
#include <QMainWindow>
#include <ui_MainWindow.h>

namespace Ui
{
    class MainWindow;
}

namespace sterm
{
    class TerminalBase;

    class MainWindow : public QMainWindow
    {
    Q_OBJECT

        std::unique_ptr<Ui::MainWindow> ui_;
        std::unique_ptr<QFont>          defFont_;
        std::unique_ptr<TerminalBase>   term_;

    public:
        MainWindow();
        ~MainWindow() override;

    public slots:
        void on_action_Exit_triggered();

    };
}

#endif //STERM_MAINWINDOW_HPP
