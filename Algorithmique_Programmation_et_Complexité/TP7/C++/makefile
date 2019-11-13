main : main.o avl.o element.o
	g++ -o main main.o avl.o element.o
	echo main > .gitignore
	echo main.o >> .gitignore
	echo avl.o >> .gitignore
	echo element.o >> .gitignore
element.o : element.cpp
	g++ -c element.cpp
	echo main > .gitignore
	echo main.o >> .gitignore
	echo avl.o >> .gitignore
	echo element.o >> .gitignore
avl.o : avl.cpp
	g++ -c avl.cpp -std=c++0x
	echo main > .gitignore
	echo main.o >> .gitignore
	echo avl.o >> .gitignore
	echo element.o >> .gitignore
main.o : main.cpp
	g++ -c main.cpp
	echo main > .gitignore
	echo main.o >> .gitignore
	echo avl.o >> .gitignore
	echo element.o >> .gitignore
run :
	./main

clean :
	rm main main.o avl.o element.o
