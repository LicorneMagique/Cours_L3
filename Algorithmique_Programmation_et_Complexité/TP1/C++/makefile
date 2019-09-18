main : main.o liste.o element.o
	g++ -o main main.o liste.o element.o
	echo main > .gitignore
	echo main.o >> .gitignore
	echo liste.o >> .gitignore
	echo element.o >> .gitignore
element.o : element.cpp
	g++ -c element.cpp
	echo main > .gitignore
	echo main.o >> .gitignore
	echo liste.o >> .gitignore
	echo element.o >> .gitignore
liste.o : liste.cpp
	g++ -c liste.cpp -std=c++0x
	echo main > .gitignore
	echo main.o >> .gitignore
	echo liste.o >> .gitignore
	echo element.o >> .gitignore
main.o : main.cpp
	g++ -c main.cpp
	echo main > .gitignore
	echo main.o >> .gitignore
	echo liste.o >> .gitignore
	echo element.o >> .gitignore
run :
	./main

clean :
	rm main main.o liste.o element.o
