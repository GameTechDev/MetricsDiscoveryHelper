:: Copyright 2019 Intel Corporation
:: 
:: Permission is hereby granted, free of charge, to any person obtaining a copy
:: of this software and associated documentation files (the "Software"), to
:: deal in the Software without restriction, including without limitation the
:: rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
:: sell copies of the Software, and to permit persons to whom the Software is
:: furnished to do so, subject to the following conditions:
:: 
:: The above copyright notice and this permission notice shall be included in
:: all copies or substantial portions of the Software.
:: 
:: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
:: IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
:: FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
:: AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
:: LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
:: FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
:: IN THE SOFTWARE.

@echo off
setlocal enabledelayedexpansion
set output_path=%1
set output_dir=%~dp1
set output_dir_short=%~dps1
set version_major=%2
set version_minor=%3
set version_git=0

if not exist %output_dir_short%NUL (
    mkdir "%output_dir%"
    if not !errorlevel!==0 exit /b 1
)

if exist %output_path% del /Q /F %output_path%

set git_path=
for %%a in (git.exe) do set git_path=%%~$PATH:a
if "%git_path%"=="" (
    echo warning: git not found in your PATH, built version will not include latest commit hash
) else (
    for /f %%a in ('"%git_path%" rev-parse HEAD') do set version_git=%%a
)

echo enum {>%output_path%
echo     MDH_VERSION_MAJOR = %version_major%,>>%output_path%
echo     MDH_VERSION_MINOR = %version_minor%,>>%output_path%
echo     MDH_VERSION_GIT   = 0x%version_git:~0,8%,>>%output_path%
echo };>>%output_path%

if not exist %output_path% exit /b 1
exit /b 0
