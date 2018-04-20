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

#ifndef STERM_SETTINGS_HPP
#define STERM_SETTINGS_HPP

#include <tuple>
#include <memory>
#include <string>
#include <string_view>
#include <cstdint>

#include <QStringList>

class QSettings;

namespace sterm
{
    class Settings
    {
        std::unique_ptr<QSettings> settings_;

    public:
        Settings(std::string_view appName);
        Settings(const Settings&) = delete;
        Settings(Settings&&) = delete;
        Settings& operator=(const Settings&) = delete;
        Settings& operator=(Settings&&) = delete;
        ~Settings() = default;

        static Settings& get();

        const QStringList loadSystemPortList() const;

        QString loadDefaultPort() const;
        void saveDefaultPort(const QString& port) const;

        std::tuple<std::string, intptr_t, intptr_t, bool> loadTerminalFont() const;
        void saveTerminalFont(std::string_view family,
                              intptr_t pointSize,
                              intptr_t weight,
                              bool italic) const;

        /**
         * @return RGBA
         */
        std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> loadColorBackground() const;
        void saveColorBackground(uint8_t r, uint8_t g, uint8_t b, uint8_t a) const;

        std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> loadColorForeground() const;
        void saveColorForeground(uint8_t r, uint8_t g, uint8_t b, uint8_t a) const;
    };
}

#endif //STERM_SETTINGS_HPP
