compile.exe: src\main.c src\string.c src\token.c src\lexer.c
	cl /Fobuild\ /Fecompile.exe $**

