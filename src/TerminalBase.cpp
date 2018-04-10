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
#include <stdexcept>

#include <fmt/format.h>

using namespace std::literals;

namespace
{
    constexpr size_t kNsecInSec = 1000000;
}

namespace sterm
{
    void TerminalBase::printRaw(std::string_view s)
    {
        outRawString(s);
    }

    void TerminalBase::printLine(std::string_view s)
    {
        outRawString(s);
        outRawString("\n"sv);
    }

    void TerminalBase::printLineTm(std::string_view s)
    {
        outRawString(fmt::format("[{}]: {}\n", getCurrentTime(), s));
    }

    std::string TerminalBase::getCurrentTime()
    {
        char            buf[128];
        struct timespec ts;

        if (timespec_get(&ts, TIME_UTC) != TIME_UTC)
        {
            throw std::runtime_error("timespec_get()");
        }

        const size_t len = strftime(buf, sizeof(buf), "%T", localtime(&ts.tv_sec));

        if (len == 0)
        {
            throw std::runtime_error("strftime()");
        }

        return fmt::format("{}.{}", buf, ts.tv_nsec / kNsecInSec);
    }
}
