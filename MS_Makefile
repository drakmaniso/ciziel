all: build compile.exe

compile.exe: src\main.c src\global.c src\string.c src\token.c src\scanner.c src\parser.c
	cl /Fobuild\ /Fecompile.exe $**

build:
	mkdir build

clean:
	del build\*.obj
