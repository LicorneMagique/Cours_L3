main : main.o liste.o element.o
	gcc -o main main.o liste.o element.o
	echo main > .gitignore
	echo main.o >> .gitignore
	echo liste.o >> .gitignore
	echo element.o >> .gitignore
element.o : element.c
	gcc -c element.c
	echo main > .gitignore
	echo main.o >> .gitignore
	echo liste.o >> .gitignore
	echo element.o >> .gitignore
liste.o : liste.c
	gcc -c liste.c
	echo main > .gitignore
	echo main.o >> .gitignore
	echo liste.o >> .gitignore
	echo element.o >> .gitignore
main.o : main.c
	gcc -c main.c
	echo main > .gitignore
	echo main.o >> .gitignore
	echo liste.o >> .gitignore
	echo element.o >> .gitignore

run :
	./main

clean :
	rm main main.o liste.o element.o
