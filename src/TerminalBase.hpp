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

#ifndef STERM_TERMINALBASE_HPP
#define STERM_TERMINALBASE_HPP

#include <string>
#include <QString>
#include <QColor>
#include <QFont>

namespace sterm
{
    class TerminalBase
    {
    public:
        TerminalBase() = default;
        TerminalBase(const TerminalBase&) = default;
        TerminalBase(TerminalBase&&) = default;
        TerminalBase& operator=(const TerminalBase&) = default;
        TerminalBase& operator=(TerminalBase&&) = default;
        virtual ~TerminalBase() = default;

        virtual void setColorBackground(const QColor& color) = 0;
        virtual void setColorForeground(const QColor& color) = 0;
        virtual void setFont(const QFont& font) = 0;

        void PrintLine(const QString& s);
        void PrintLine(const std::string& s);
        void PrintLineTm(const QString& s);
        void PrintLineTm(const std::string& s);

    protected:
        virtual void outString(const QString& s) = 0;
    };
}

#endif //STERM_TERMINALBASE_HPP
