@echo off
"C:\Program Files\Epic Games\UE_5.7\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe" SLF_5_7Editor Development Win64 -project="C:\scripts\BlueDestiny\SLF_5_7.uproject" -WaitMutex -MaxParallelActions=4
if %ERRORLEVEL% NEQ 0 (
  echo Build Failed
  exit /b %ERRORLEVEL%
)
echo Build Successful
