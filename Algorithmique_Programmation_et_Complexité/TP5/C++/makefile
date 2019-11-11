main : main.o abr.o element.o
	g++ -o main main.o abr.o element.o
	echo main > .gitignore
	echo main.o >> .gitignore
	echo abr.o >> .gitignore
	echo element.o >> .gitignore
element.o : element.cpp
	g++ -c element.cpp
	echo main > .gitignore
	echo main.o >> .gitignore
	echo abr.o >> .gitignore
	echo element.o >> .gitignore
abr.o : abr.cpp
	g++ -c abr.cpp -std=c++0x
	echo main > .gitignore
	echo main.o >> .gitignore
	echo abr.o >> .gitignore
	echo element.o >> .gitignore
main.o : main.cpp
	g++ -c main.cpp
	echo main > .gitignore
	echo main.o >> .gitignore
	echo abr.o >> .gitignore
	echo element.o >> .gitignore
run :
	./main

clean :
	rm main main.o abr.o element.o
