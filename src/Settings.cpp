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

#include <stdexcept>
#include <string_view>

#include <QString>
#include <QSettings>
#include <QMainWindow>
#include <QApplication>
#include <QDesktopWidget>

#include "Version.hpp"

#include <fmt/format.h>

namespace
{
    constexpr double kDefaultWindowSize = 0.8;

    /// Zero terminated string (std::data(str) is safe).
    constexpr std::string_view kCommonGroup               = "Common";
    constexpr std::string_view kCommonDefaultPort         = "DefaultPort";
    constexpr std::string_view kCommonMainWindowSize      = "MainWindowSize";
    constexpr std::string_view kCommonMainWindowPosition  = "MainWindowPosition";
    constexpr std::string_view kCommonMainWindowMaximized = "MainWindowMaximized";

    constexpr std::string_view kTerminalGroup           = "Terminal";
    constexpr std::string_view kTerminalFontName        = "FontName";
    constexpr std::string_view kTerminalFontSize        = "FontSize";
    constexpr std::string_view kTerminalFontWeight      = "FontWeight";
    constexpr std::string_view kTerminalFontItalic      = "FontItalic";
    constexpr std::string_view kTerminalBackgroundColor = "BackgroundRgba";
    constexpr std::string_view kTerminalForegroundColor = "ForegroundRgba";
}

namespace detail
{
    bool hexColorIsValid(const QString& hexColor)
    {
        return (hexColor.length() == 10) && hexColor.startsWith("0x");
    }

    std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> hexToRgb(QString hexColor)
    {
        if (!hexColorIsValid(hexColor))
        {
            throw std::invalid_argument{"Invalid hexColor value!"};
        }

        hexColor = hexColor.remove(0, 2); /// Remove "0x" prefix
        const auto r = static_cast<uint8_t>(std::stoul(hexColor.left(2).toStdString(), nullptr, 16));
        hexColor = hexColor.remove(0, 2);
        const auto g = static_cast<uint8_t>(std::stoul(hexColor.left(2).toStdString(), nullptr, 16));
        hexColor = hexColor.remove(0, 2);
        const auto b = static_cast<uint8_t>(std::stoul(hexColor.left(2).toStdString(), nullptr, 16));
        hexColor = hexColor.remove(0, 2);
        const auto a = static_cast<uint8_t>(std::stoul(hexColor.left(2).toStdString(), nullptr, 16));

        return {r, g, b, a};
    }

    QString rgbToHex(std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> color)
    {
        return fmt::format("{:#04x}{:02x}{:02x}{:02x}",
                           std::get<0>(color),
                           std::get<1>(color),
                           std::get<2>(color),
                           std::get<3>(color)).c_str();
    }

    QMainWindow* getMainWindow()
    {
        for (auto& w: QApplication::topLevelWidgets())
        {
            QMainWindow* mainWindow = qobject_cast<QMainWindow*>(w);

            if (mainWindow)
            {
                return mainWindow;
            }
        }

        return nullptr;
    }
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

    QString Settings::loadDefaultPort() const
    {
        settings_->beginGroup(std::data(kCommonGroup));
        auto port = settings_->value(std::data(kCommonDefaultPort)).toString();
        settings_->endGroup();
        saveDefaultPort(port);
        return port;
    }

    void Settings::saveDefaultPort(const QString& port) const
    {
        settings_->beginGroup(std::data(kCommonGroup));
        settings_->setValue(std::data(kCommonDefaultPort), port);
        settings_->endGroup();
    }

    std::tuple<std::string, intptr_t, intptr_t, bool> Settings::loadTerminalFont() const
    {
        settings_->beginGroup(std::data(kTerminalGroup));
        const QString  fontName   = settings_->value(std::data(kTerminalFontName), "Liberation Mono")
                                             .toString();
        const intptr_t fontSize   = settings_->value(std::data(kTerminalFontSize), 12).toInt();
        const intptr_t fontWeight = settings_->value(std::data(kTerminalFontWeight), -1).toInt();
        const bool     fontItalic = settings_->value(std::data(kTerminalFontItalic), false).toBool();
        settings_->endGroup();
        saveTerminalFont(fontName.toStdString(), fontSize, fontWeight, fontItalic);
        return {fontName.toStdString(), fontSize, fontWeight, fontItalic};
    }

    void Settings::saveTerminalFont(std::string_view family,
                                    intptr_t pointSize,
                                    intptr_t weight,
                                    bool italic) const
    {
        settings_->beginGroup(std::data(kTerminalGroup));
        settings_->setValue(std::data(kTerminalFontName),
                            QString::fromUtf8(std::data(family), static_cast<int>(std::size(family))));
        settings_->setValue(std::data(kTerminalFontSize), static_cast<int>(pointSize));
        settings_->setValue(std::data(kTerminalFontWeight), static_cast<int>(weight));
        settings_->setValue(std::data(kTerminalFontItalic), italic);
        settings_->endGroup();
    }

    std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> Settings::loadColorBackground() const
    {
        constexpr std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> defValue = {46, 52, 54, 255};

        settings_->beginGroup(std::data(kTerminalGroup));
        QString rgba = settings_->value(std::data(kTerminalBackgroundColor), "").toString();
        settings_->endGroup();

        if (!detail::hexColorIsValid(rgba))
        {
            saveColorBackground(std::get<0>(defValue),
                                std::get<1>(defValue),
                                std::get<2>(defValue),
                                std::get<3>(defValue));
            return defValue;
        }

        return detail::hexToRgb(rgba);
    }

    void Settings::saveColorBackground(uint8_t r, uint8_t g, uint8_t b, uint8_t a) const
    {
        settings_->beginGroup(std::data(kTerminalGroup));
        settings_->setValue(std::data(kTerminalBackgroundColor), detail::rgbToHex({r, g, b, a}));
        settings_->endGroup();
    }

    std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> Settings::loadColorForeground() const
    {
        constexpr std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> defValue = {117, 231, 9, 255};

        settings_->beginGroup(std::data(kTerminalGroup));
        QString rgba = settings_->value(std::data(kTerminalForegroundColor), "").toString();
        settings_->endGroup();

        if (!detail::hexColorIsValid(rgba))
        {
            saveColorForeground(std::get<0>(defValue),
                                std::get<1>(defValue),
                                std::get<2>(defValue),
                                std::get<3>(defValue));
            return defValue;
        }

        return detail::hexToRgb(rgba);
    }

    void Settings::saveColorForeground(uint8_t r, uint8_t g, uint8_t b, uint8_t a) const
    {
        settings_->beginGroup(std::data(kTerminalGroup));
        settings_->setValue(std::data(kTerminalForegroundColor), detail::rgbToHex({r, g, b, a}));
        settings_->endGroup();
    }

    QSize Settings::loadMainWindowSize() const
    {
        settings_->beginGroup(std::data(kCommonGroup));
        auto size = settings_->value(std::data(kCommonMainWindowSize), QSize{0, 0}).toSize();
        settings_->endGroup();

        if (size.isNull())
        {
            auto desk = QApplication::desktop();
            size = desk->availableGeometry(desk->primaryScreen()).size() * kDefaultWindowSize;
        }

        saveMainWindowSize(size);
        return size;
    }

    void Settings::saveMainWindowSize(const QSize& size) const
    {
        settings_->beginGroup(std::data(kCommonGroup));
        settings_->setValue(std::data(kCommonMainWindowSize), size);
        settings_->endGroup();
    }

    QPoint Settings::loadMainWindowPosition() const
    {
        settings_->beginGroup(std::data(kCommonGroup));
        auto position = settings_->value(std::data(kCommonMainWindowPosition), QPoint{0, 0}).toPoint();
        settings_->endGroup();

        if (position.isNull())
        {
            auto mainWindow = detail::getMainWindow();

            if (mainWindow)
            {
                auto desk = QApplication::desktop();
                position = desk->availableGeometry(desk->primaryScreen()).center() -
                           mainWindow->rect().center();
            }
        }

        saveMainWindowPosition(position);
        return position;
    }

    void Settings::saveMainWindowPosition(const QPoint& position) const
    {
        settings_->beginGroup(std::data(kCommonGroup));
        settings_->setValue(std::data(kCommonMainWindowPosition), position);
        settings_->endGroup();
    }

    bool Settings::loadMainWindowMaximizedState() const
    {
        settings_->beginGroup(std::data(kCommonGroup));
        auto maximized = settings_->value(std::data(kCommonMainWindowMaximized), false).toBool();
        settings_->endGroup();
        saveMainWindowMaximizedState(maximized);
        return maximized;
    }

    void Settings::saveMainWindowMaximizedState(bool maximized) const
    {
        settings_->beginGroup(std::data(kCommonGroup));
        settings_->setValue(std::data(kCommonMainWindowMaximized), maximized);
        settings_->endGroup();
    }
}
