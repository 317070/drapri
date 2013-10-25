pushd %~dp0..\..\src
if exist %~dp0..\..\src\build rmdir /s /q %~dp0..\..\src\build
if exist %~dp0..\..\src\dist rmdir /s /q %~dp0..\..\src\dist
if exist %~dp0..\..\src\MANIFEST del /s %~dp0..\..\src\MANIFEST
if exist %~dp0..\..\src\smartcard\scard\scard.py del /s %~dp0..\..\src\smartcard\scard\scard.py
if exist %~dp0..\..\src\smartcard\scard\scard_wrap.c del /s %~dp0..\..\src\smartcard\scard\scard_wrap.c
if exist %~dp0..\..\src\smartcard\Examples\wx\apdumanager\SampleAPDUManagerPanel.pyc del /s %~dp0..\..\src\smartcard\Examples\wx\apdumanager\SampleAPDUManagerPanel.pyc
if exist %~dp0..\..\src\smartcard\Examples\framework\ExclusiveConnectCardConnection.pyc del /s %~dp0..\..\src\smartcard\Examples\framework\ExclusiveConnectCardConnection.pyc
if exist %~dp0..\..\src\smartcard\Examples\framework\ExclusiveTransmitCardConnection.pyc del /s %~dp0..\..\src\smartcard\Examples\framework\ExclusiveTransmitCardConnection.pyc
popd

