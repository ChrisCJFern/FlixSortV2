#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

struct movie {
	unsigned int budget;
	string company;
	string country;
	string director;
	string genre;
	unsigned int gross;
	string name;
	double rating;
	string releaseDate;
	int runtime;
	double score;
	string star;
	int votes;
	string writer; 
	int year;
};

int main() {
	cout << setfill('=') << setw(51);
	cout << "\n";
	cout << "|              Welcome to FlixSort               |" << endl;
	cout << "|     Est. 2020 by the Magical Movie Masters     |" << endl;
	cout << "|><><><><><><><><><><><><><><><><><><><><><><><><|" << endl;
	cout << "|1. Want to watch a movie marathon?              |" << endl;
	cout << "|2. Can't decide what movie to watch?            |" << endl;
	cout << "|             We can choose for you!             |" << endl;
	cout << setfill('=') << setw(51);
	cout << "\n";

	string line;
	ifstream movieFile;
	movieFile.open("movies.csv", ios::in);
	if (movieFile.is_open()) {
		getline(movieFile, line);
		cout << line << endl;
		movieFile.close();
	}


	return 0;
}