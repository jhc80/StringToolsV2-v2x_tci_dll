call env.bat

SET PNAME=window

del %OUTPUT_PATH%\*.* /Q
del %PNAME%.ncb

"%MSDevdir%\Bin\MSDev.exe" %PNAME%.dsw

IF EXIST %OUTPUT_PATH%\%PNAME%.exe (
del %PNAME%.exe
copy %OUTPUT_PATH%\%PNAME%.exe %PNAME%.exe
)

del %OUTPUT_PATH%\*.* /Q
del %PNAME%.ncb
