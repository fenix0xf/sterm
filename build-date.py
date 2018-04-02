#!/usr/bin/python3

#
# MIT License
#
# Copyright (c) 2018 Alexander Kotikov <alexandr.kotikov@gmail.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

from datetime import datetime, timezone
import time
import pathlib
import sys

if len(sys.argv) != 2:
    print("Error: Invalid parameters!", file=sys.stderr)
    exit(1)

outFileName = sys.argv[1]

outTextFmt = \
    "/**\n" \
    " * Auto generated build date header.\n" \
    " *\n" \
    " * @details\n" \
    " *\n" \
    " * BUILD_DATE is seconds since 1970-01-01 00:00:00 UTC (UNIX Epoch).\n" \
    " * BUILD_DATE_STR is current UTC time string.\n" \
    " * BUILD_DATE_LSTR is current Local time string.\n" \
    " *\n" \
    " */\n\n" \
    "#include <ctime>\n\n" \
    "const time_t BUILD_DATE        = {0}; ///< {1}\n" \
    "const char   BUILD_DATE_STR[]  = \"{1}\";\n" \
    "const char   BUILD_DATE_LSTR[] = \"{2}\";\n"

utc = datetime.utcnow().replace(tzinfo=timezone.utc)
local = utc.astimezone(tz=None)

unixTimeUTC = str(int(time.mktime(local.timetuple())))
tfmt = "%a %d %b %Y %H:%M:%S %z"
utcStr = utc.strftime(tfmt)
localStr = local.strftime(tfmt)

outText = outTextFmt.format(unixTimeUTC, utcStr, localStr)

outFile = pathlib.Path(outFileName)
outFile.write_text(outText)
