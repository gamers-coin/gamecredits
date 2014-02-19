@call set_vars.bat
@bash patch_files.sh
@echo Building Bitcoin daemon...
@rem todo: rewrite this with ^ line wrapping
@set PARAMS=BOOST_SUFFIX=%BOOSTSUFFIX%
@set PARAMS=%PARAMS% INCLUDEPATHS="
@rem set PARAMS=%PARAMS%-I'%CD%/../src'
@set PARAMS=%PARAMS% -I'%CD%/../%EWBLIBS%/%BOOST%'
@set PARAMS=%PARAMS% -I'%CD%/../%EWBLIBS%/%OPENSSL%/include'
@set PARAMS=%PARAMS% -I'%CD%/../%EWBLIBS%/%BERKELEYDB%/build_unix'
@set PARAMS=%PARAMS% -I'%CD%/../%EWBLIBS%/%MINIUPNPC%'
@set PARAMS=%PARAMS%"
@set PARAMS=%PARAMS% LIBPATHS="
@set PARAMS=%PARAMS%-L'%CD%/../src/leveldb'
@set PARAMS=%PARAMS% -L'%CD%/../%EWBLIBS%/%BOOST%/stage/lib'
@set PARAMS=%PARAMS% -L'%CD%/../%EWBLIBS%/%OPENSSL%'
@set PARAMS=%PARAMS% -L'%CD%/../%EWBLIBS%/%BERKELEYDB%/build_unix'
@set PARAMS=%PARAMS% -L'%CD%/../%EWBLIBS%/%MINIUPNPC%'
@set PARAMS=%PARAMS%"
@set PARAMS=%PARAMS% ADDITIONALCCFLAGS="%ADDITIONALCCFLAGS%"
@set PARAMS=%PARAMS:\=/%
@echo PARAMS: %PARAMS%

@set PARAMS=%PARAMS% USE_UPNP=1
@rem remove "rem " from the next line to deactivate upnp
@rem set PARAMS=%PARAMS% USE_UPNP=-

@cd ..\src
@mingw32-make -f makefile.mingw %PARAMS%
@if errorlevel 1 goto error
@echo.
@echo.
@strip %COINNAME%d.exe
@if errorlevel 1 goto error
@echo !!!!!!! %COINNAME% daemon DONE: Find %COINNAME%d.exe in ./src :)
@echo.
@echo.
@if not "%RUNALL%"=="1" pause
@goto end

:error
@echo.
@echo.
@echo !!!!!! Error! Build daemon failed.
@pause
:end
@cd ..\easywinbuilder
