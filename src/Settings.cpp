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

#include <QString>
#include <QSettings>
#include <Version.hpp>

namespace
{
    const char CommonGroup[] = "Common";
    const char PortList[]    = "PortList";
}

namespace sterm
{
    Settings::Settings()
        : settings_{std::make_unique<QSettings>(QString::fromStdString(APP_SHORT_NAME),
                                                QString::fromStdString(APP_SHORT_NAME))}
    {
    }

    Settings& Settings::get()
    {
        static Settings settings{};
        return settings;
    }

    const QStringList Settings::getPortList() const
    {
        return QStringList{};
    }

    void Settings::setPortList(const QStringList& list)
    {
        settings_->beginGroup(CommonGroup);
        settings_->beginWriteArray(PortList, list.count());

        for (int i = 0; i < list.count(); ++i)
        {
            settings_->setArrayIndex(i);
            settings_->setValue("value", list.at(i));
        }

        settings_->endArray();
        settings_->endGroup();
    }
}
