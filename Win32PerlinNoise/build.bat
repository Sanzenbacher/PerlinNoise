@echo off
REM  Run vc Build Tools
call "C:\Program Files (x86)\Microsoft Visual C++ Build Tools\vcbuildtools.bat" x64    
set compilerflags=-Od -MTd -nologo -fp:fast -fp:except- -Gm- -GR- -EHsc- -Zo -Oi -WX -W4 -wd4201 -wd4100 -wd4189 -wd4505 -wd4127 -wd4244 -FC -Z7
set linkerflags=/OUT:win64_perlinnoise.exe  -incremental:no -opt:ref user32.lib gdi32.lib winmm.lib opengl32.lib
cd C:\SGD\PerlinNoise
cl.exe %compilerflags% PerlinNoise\PerlinNoiseGenerator.cpp Win32PerlinNoise\win32_handmade.cpp /link %linkerflags%