main : main.o table.o
	g++ -o main main.o table.o
	echo main > .gitignore
	echo main.o >> .gitignore
	echo table.o >> .gitignore
element.o : table.cpp
	g++ -c table.cpp
	echo main > .gitignore
	echo main.o >> .gitignore
	echo table.o >> .gitignore
main.o : main.cpp
	g++ -c main.cpp
	echo main > .gitignore
	echo main.o >> .gitignore
	echo table.o >> .gitignore
run :
	./main

clean :
	rm main .gitignore *.o *.txt
