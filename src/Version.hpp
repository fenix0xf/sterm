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

#ifndef STERM_VERSION_HPP
#define STERM_VERSION_HPP

#include <ctime>
#include <cstddef>
#include <string>
#include <string_view>

namespace sterm
{
    class Version
    {
        size_t major_;
        size_t minor_;
        size_t revision_;
        time_t buildTime_;

        Version(size_t major, size_t minor, size_t revision, time_t buildTime);

    public:
        Version() = delete;
        Version(const Version&) = delete;
        Version(Version&&) = delete;
        Version& operator=(const Version&) = delete;
        Version& operator=(Version&&) = delete;
        ~Version() = default;

        size_t getMajor() const
        {
            return major_;
        }

        size_t getMinor() const
        {
            return minor_;
        }

        size_t getRevision() const
        {
            return revision_;
        }

        time_t getBuildUnixTime() const
        {
            return buildTime_;
        }

        std::string getVersionString() const;
        std::string_view getBuildDate() const;
        std::string_view getAppName() const;
        std::string_view getAppShortName() const;
        std::string getAppNameAndVersion() const;

        static const Version& get();
    };
}

#endif //STERM_VERSION_HPP
