call env.bat

SET PNAME=dll

del %OUTPUT_PATH%\*.* /Q
del %PNAME%.ncb

"%MSDevdir%\Bin\MSDev.exe" %PNAME%.dsw

IF EXIST %OUTPUT_PATH%\%PNAME%.dll (
del %PNAME%.dll
copy %OUTPUT_PATH%\%PNAME%.dll %PNAME%.dll
)

del %OUTPUT_PATH%\*.* /Q
del %PNAME%.ncb
