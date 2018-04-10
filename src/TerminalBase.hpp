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

#include <string_view>

namespace sterm
{
    class TerminalBase
    {
        virtual void outRawString(std::string_view s) = 0;
        std::string getCurrentTime();

    public:
        TerminalBase() = default;
        TerminalBase(const TerminalBase&) = default;
        TerminalBase(TerminalBase&&) = default;
        TerminalBase& operator=(const TerminalBase&) = default;
        TerminalBase& operator=(TerminalBase&&) = default;
        virtual ~TerminalBase() = default;

        virtual void setColorBackground(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) = 0;
        virtual void setColorForeground(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) = 0;
        virtual void setFont(std::string_view family,
                             intptr_t pointSize = -1,
                             intptr_t weight = -1,
                             bool italic = false) = 0;

        void printRaw(std::string_view s);
        void printLine(std::string_view s);
        void printLineTm(std::string_view s);
    };
}

#endif //STERM_TERMINALBASE_HPP
