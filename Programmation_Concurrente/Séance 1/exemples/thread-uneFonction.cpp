// g++ thread-uneFonction.cpp -std=c++11 -pthread
#include <thread>
#include <iostream>
using namespace std;

int num = 3;
void uneFonction(int i, string mess) {
	cout << "Je suis le thread " << i
	     << " mon message est : " << mess << endl;
	num = num+10;
}
int main() {
	string message = "coucou";
	thread t(uneFonction, 1, message);
	// ...
	t.join();
	cout << "Le nombre est :" << num << endl;
}
