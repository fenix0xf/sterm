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
#include <string_view>

#include <QString>
#include <QSettings>

#include "Version.hpp"

using namespace std::literals;

namespace
{
    /// Zero terminated string (str.data() is safe).
    constexpr std::string_view kCommonGroup = "Common"sv;
    constexpr std::string_view kDefaultPort = "DefaultPort"sv;
}

namespace sterm
{
    Settings::Settings(std::string_view appName)
        : settings_{std::make_unique<QSettings>(QString::fromUtf8(std::data(appName),
                                                                  static_cast<int>(std::size(appName))),
                                                QString::fromUtf8(std::data(appName),
                                                                  static_cast<int>(std::size(appName))))}
    {
    }

    Settings& Settings::get()
    {
        static Settings settings{Version::get().getAppShortName()};
        return settings;
    }

    QString Settings::getDefaultPort() const
    {
        settings_->beginGroup(kCommonGroup.data());
        QString ret = settings_->value(kDefaultPort.data()).toString();
        settings_->endGroup();
        return ret;
    }

    void Settings::setDefaultPort(const QString& port)
    {
        settings_->beginGroup(kCommonGroup.data());
        settings_->setValue(kDefaultPort.data(), port);
        settings_->endGroup();
    }
}
