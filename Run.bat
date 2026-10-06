@echo off
:menu
set /p choice="Choose mode (Host(h) or Client(c)): "

:: Convert input to lowercase and check choices
if /i "%choice%"=="h" goto host_mode
if /i "%choice%"=="c" goto client_mode

:: If they type anything else, restart the menu
echo Invalid choice, please type 'h' or 'c'.
echo.
goto menu

:host_mode
echo You chose Host Mode!
start "" "ShipRush.exe" h
pause
exit

:client_mode
echo You chose Client Mode!
start "" "ShipRush.exe" c
pause
exit
