if exist %~dp0..\..\generated pushd %~dp0..\..\generated
if exist %~dp0..\..\generated\doc rmdir /s /q %~dp0..\..\generated\doc
if exist %~dp0..\..\generated\pyscard-doc.zip del /s /q %~dp0..\..\generated\pyscard-doc.zip
if exist %~dp0..\..\generated popd

