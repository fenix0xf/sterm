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

#include "Version.hpp"
#include <fmt/format.h>

#include "BuildInfo.hpp"

using namespace std::literals;

namespace
{
    constexpr size_t kVersionMajor    = 0;
    constexpr size_t kVersionMinor    = 2;
    constexpr size_t kVersionRevision = 2;

    constexpr std::string_view kAppName{"Serial Terminal"sv};
    constexpr std::string_view kAppShortName{"sterm"sv};
}

#ifdef DEBUG
#define APP_DEBUG   " debug"
#else
#define APP_DEBUG   ""
#endif

namespace sterm
{
    Version::Version(size_t major, size_t minor, size_t revision, time_t buildTime)
        : major_(major),
          minor_(minor),
          revision_(revision),
          buildTime_(buildTime)
    {
    }

    std::string Version::getVersionString() const
    {
        return fmt::format("v{:d}.{:d}.{:d}" APP_DEBUG, getMajor(), getMinor(), getRevision());
    }

    std::string_view Version::getBuildDate() const
    {
        return build_info::BUILD_DATE_LSTR;
    }

    std::string_view Version::getAppName() const
    {
        return kAppName;
    }

    std::string_view Version::getAppShortName() const
    {
        return kAppShortName;
    }

    std::string Version::getAppNameAndVersion() const
    {
        return fmt::format("{:s} {:s}", getAppName(), getVersionString());
    }

    const Version& Version::get()
    {
        static const Version version{kVersionMajor, kVersionMinor, kVersionRevision, build_info::BUILD_DATE};
        return version;
    }
}
