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

#include "TerminalBase.hpp"

#include <ctime>
#include <fmt/format.h>

namespace sterm
{
    void TerminalBase::printRaw(const std::string& s)
    {
        outRawString(s);
    }

    void TerminalBase::printLine(const std::string& s)
    {
        outRawString(s + '\n');
    }

    void TerminalBase::printLineTm(const std::string& s)
    {


        outRawString(fmt::format("{}: {}\n", getCurrentTime(), s));
    }

    std::string TerminalBase::getCurrentTime()
    {
        char s[128];
        auto t = time(nullptr);
        strftime(s, sizeof(s), "%T", localtime(&t));
        return std::string{s};
    }
}
