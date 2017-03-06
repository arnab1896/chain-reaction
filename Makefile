project : codemain.o code.o
	gcc codemain.o code.o -lncurses -o project
codemain.o : codemain.c code.h
	gcc -c codemain.c
code.o : code.c code.h
	gcc -c code.c
	
