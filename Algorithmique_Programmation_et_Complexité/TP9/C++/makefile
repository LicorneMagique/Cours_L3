main : main.o graphe.o
	g++ -o main main.o graphe.o
	echo main > .gitignore
	echo main.o >> .gitignore
	echo graphe.o >> .gitignore
graphe.o : graphe.cpp
	g++ -c graphe.cpp -std=c++0x
	echo main > .gitignore
	echo main.o >> .gitignore
	echo graphe.o >> .gitignore
main.o : main.cpp
	g++ -c main.cpp
	echo main > .gitignore
	echo main.o >> .gitignore
	echo graphe.o >> .gitignore

clean :
	rm main main.o graphe.o
