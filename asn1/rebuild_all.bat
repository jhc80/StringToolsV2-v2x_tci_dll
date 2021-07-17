call menv.bat

SET ROOT_PATH=%CD%
cd %ROOT_PATH%/gxx_obu_dll
make clean
make

if %ERRORLEVEL% NEQ 0 (
    echo "run make fail."
    goto END
)

cd %ROOT_PATH%/v2x_gb2017_dll
make clean
make

if %ERRORLEVEL% NEQ 0 (
    echo "run make fail."
    goto END
)

cd %ROOT_PATH%/v2x_gb2019_dll
make clean
make

if %ERRORLEVEL% NEQ 0 (
    echo "run make fail."
    goto END
)

cd %ROOT_PATH%/v2x_gb2020_dll
make clean
make

if %ERRORLEVEL% NEQ 0 (
    echo "run make fail."
    goto END
)

cd %ROOT_PATH%/v2x_gb2020_day2_dll
make clean
make

echo "SUCCESS"

:END
pause


