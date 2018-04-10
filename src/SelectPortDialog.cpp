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

#include "SelectPortDialog.hpp"

#include <ui_SelectPortDialog.h>
#include "Settings.hpp"

namespace sterm
{
    SelectPortDialog::SelectPortDialog(QWidget* parent)
        : QDialog(parent),
          selectPortDialog_{std::make_unique<Ui::SelectPortDialog>()}
    {
        selectPortDialog_->setupUi(this);
        selectPortDialog_->portComboBox->addItems(Settings::get().getSystemPortList());

        const auto defaultPort = Settings::get().getDefaultPort();

        if (int idx = selectPortDialog_->portComboBox->findText(defaultPort); idx != -1)
        {
            selectPortDialog_->portComboBox->setCurrentIndex(idx);
        }
        else
        {
            selectPortDialog_->portComboBox->setCurrentText(defaultPort);
        }
    }

    SelectPortDialog::~SelectPortDialog()
    {
        Settings::get().setDefaultPort(selectPortDialog_->portComboBox->currentText());
    }

    QString SelectPortDialog::getPort()
    {
        return selectPortDialog_->portComboBox->currentText();
    }
}
