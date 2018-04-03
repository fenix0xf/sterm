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

#include "PlainTextTerminal.hpp"

#include <QPlainTextEdit>
#include <QFont>

namespace sterm
{
    PlainTextTerminal::PlainTextTerminal(QPlainTextEdit& plainTextEdit)
        : plainTextEdit_{plainTextEdit}
    {
        plainTextEdit_.setReadOnly(true);
    }

    void PlainTextTerminal::outRawString(const std::string& s)
    {
        plainTextEdit_.appendPlainText(QString::fromStdString(s));
    }

    void PlainTextTerminal::setColorBackground(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        auto palette = plainTextEdit_.palette();
        palette.setColor(QPalette::Base, QColor::fromRgb(r, g, b, a));
        plainTextEdit_.setPalette(palette);
    }

    void PlainTextTerminal::setColorForeground(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        auto palette = plainTextEdit_.palette();
        palette.setColor(QPalette::Text, QColor::fromRgb(r, g, b, a));
        plainTextEdit_.setPalette(palette);
    }

    void PlainTextTerminal::setFont(const std::string& family, intptr_t pointSize, intptr_t weight, bool italic)
    {
        plainTextEdit_.setFont(QFont{QString::fromStdString(family), (int)pointSize, (int)weight, italic});
    }
}
