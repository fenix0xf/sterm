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

#include "Settings.hpp"

#include <experimental/filesystem>
#include <string_view>
#include <exception>

#include <QStringList>
#include <QSerialPortInfo>
#include <fmt/format.h>

namespace fs = std::experimental::filesystem;

namespace
{
    constexpr bool             kDebugAddTestPorts = false;
    constexpr std::string_view kSysDevDir         = "/dev";
}

namespace sterm
{
    const QStringList Settings::loadSystemPortList() const
    {
        try
        {
            auto ports = QSerialPortInfo::availablePorts();
            auto names = QStringList{};

            if constexpr (kDebugAddTestPorts)
            {
                names.append("/dev/ttyUSB-TEST0");
                names.append("/dev/ttyUSB-TEST1");
                names.append("/dev/ttyUSB-TEST2");
                names.append("/dev/ttyUSB-TEST3");
            }

            for (const auto& port : ports)
            {
                names.append(port.systemLocation());
            }

            const fs::path rootDev{kSysDevDir};

            for (const auto& entry : fs::directory_iterator(rootDev))
            {
                if (!fs::is_symlink(entry))
                {
                    continue;
                }

                auto link = rootDev / fs::read_symlink(entry);

                if (names.contains(QString::fromUtf8(std::data(link.native()),
                                                     static_cast<int>(std::size(link.native())))))
                {
                    names.append(QString::fromUtf8(std::data(entry.path().native()),
                                                   static_cast<int>(std::size(entry.path().native()))));
                }
            }

            return names;
        }
        catch (const std::exception& e)
        {
            return QStringList{e.what()};
        }
    }
}
