main : sched.o
	g++ -std=c++11 -g -Wall sched.cpp -pthread -o main
	echo main > .gitignore
	echo sched.o >> .gitignore

run :
	./main

clean :
	rm main *.o
