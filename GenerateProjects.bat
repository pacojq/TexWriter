pushd .\


echo Checking out supported spdlog version...

pushd TexWriter\vendor\spdlog
git checkout 5b4c4f3f
popd


echo Copying premake files to vendor modules...

xcopy "TexWriter\vendor\glfw-premake5.lua" "TexWriter\vendor\GLFW\premake5.lua" /Y /F
xcopy "TexWriter\vendor\imgui-premake5.lua" "TexWriter\vendor\imgui\premake5.lua" /Y /F

echo Premake files ready!

@echo off
call vendor\bin\premake\premake5.exe vs2019
popd
IF %ERRORLEVEL% NEQ 0 (
  PAUSE
)