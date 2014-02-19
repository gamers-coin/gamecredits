@call set_vars.bat
copy %QTPATH%\QtCore4.dll ..\release\
copy %QTPATH%\QtGui4.dll ..\release\
copy %QTPATH%\QtNetwork4.dll ..\release\
copy C:\MinGW\bin\libgcc_s_dw2-1.dll ..\release\
copy "C:\MinGW\bin\libstdc++-6.dll" ..\release\
copy C:\MinGW\bin\mingwm10.dll ..\release\

copy C:\MinGW\bin\libgcc_s_dw2-1.dll ..\src\
copy "C:\MinGW\bin\libstdc++-6.dll" ..\src\
@if not "%RUNALL%"=="1" pause