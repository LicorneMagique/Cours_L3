main : main.o mandel.o display.o ProdCons.o
	g++ ProdCons.cpp mandel.cpp display.cpp main.cpp -g -O0 -Wall -Wextra -L /usr/X11R6/lib/ -std=c++11 -lX11 -pthread -o main
	echo main > .gitignore
	echo main.o >> .gitignore
	echo mandel.o >> .gitignore
	echo display.o >> .gitignore
	echo ProdCons.o >> .gitignore

run :
	./main

clean :
	rm main *.o
