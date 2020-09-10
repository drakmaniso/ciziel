compile.exe: src\main.c src\string.c src\token.c src\scanner.c
	cl /Fobuild\ /Fecompile.exe $**

