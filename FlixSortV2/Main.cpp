#include <iostream>
#include <fstream>
using namespace std;

int main() {
	cout << "==================================================" << endl;
	cout << "|             Welcome to FlixSort!               |" << endl;
	cout << "|   Est. 2020 by the Magical Movie Masters :)    |" << endl;
	cout << "|   forever crying thanks to github :''''''(     |" << endl;
	cout << "==================================================" << endl;
	
	cout << "Hello" << endl;
	cout << "NO im still scared";
	cout << "grr";
	cout << 5 + 99;
	cout << "Can you see me" << endl;
	cout << "julia welcome buddyy";
	cout << "aasdadafa" << endl;
	cout << "hello my computer is no longer wack" << endl;

	ifstream movieFile;
	movieFile.open("movies.csv", ios::in);
	if (movieFile.is_open()) {
		cout << "i think it's working" << endl;
		movieFile.close();
	}
	

	return 0;
}