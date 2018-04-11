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
    constexpr std::string_view kCommonGroup       = "Common"sv;
    constexpr std::string_view kCommonDefaultPort = "DefaultPort"sv;

    constexpr std::string_view kTerminalFontGroup  = "TerminalFont"sv;
    constexpr std::string_view kTerminalFontName   = "Name"sv;
    constexpr std::string_view kTerminalFontSize   = "Size"sv;
    constexpr std::string_view kTerminalFontWeight = "Weight"sv;
    constexpr std::string_view kTerminalFontItalic = "Italic"sv;
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
        settings_->beginGroup(std::data(kCommonGroup));
        QString ret = settings_->value(kCommonDefaultPort.data()).toString();
        settings_->endGroup();
        return ret;
    }

    void Settings::setDefaultPort(const QString& port)
    {
        settings_->beginGroup(std::data(kCommonGroup));
        settings_->setValue(kCommonDefaultPort.data(), port);
        settings_->endGroup();
    }

    std::tuple<std::string, intptr_t, intptr_t, bool> Settings::getTerminalFont()
    {
        settings_->beginGroup(kTerminalFontGroup.data());
        const QString  fontName   = settings_->value(std::data(kTerminalFontName), "monospace").toString();
        const intptr_t fontSize   = settings_->value(std::data(kTerminalFontSize), 12).toInt();
        const intptr_t fontWeight = settings_->value(std::data(kTerminalFontWeight), -1).toInt();
        const bool     fontItalic = settings_->value(std::data(kTerminalFontItalic), false).toBool();
        settings_->endGroup();
        return {fontName.toStdString(), fontSize, fontWeight, fontItalic};
    }

    void Settings::setTrminalFont(std::string_view family, intptr_t pointSize, intptr_t weight, bool italic)
    {
        settings_->beginGroup(std::data(kTerminalFontGroup));
        settings_->setValue(kTerminalFontName.data(),
                            QString::fromUtf8(std::data(family), static_cast<int>(std::size(family))));
        settings_->setValue(std::data(kTerminalFontSize), static_cast<int>(pointSize));
        settings_->setValue(std::data(kTerminalFontWeight), static_cast<int>(weight));
        settings_->setValue(std::data(kTerminalFontItalic), italic);
        settings_->endGroup();
    }
}
