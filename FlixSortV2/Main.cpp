#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*
void createMovieArray(const char* filePath, vector<lego>& legos) {
	ifstream file(filePath);
	if (file.is_open()) {
		string fileLine;
		getline(file, fileLine);

		while (!file.eof()) {
			// 1. Get a line from the file (from lecture)
			getline(file, fileLine);

			// 2. Break line into separate pieces, based on comma delimiter (from lecture)
			istringstream stream(fileLine);
			string setNum, legoTheme, legoName, stringMinifigs, stringPieces, stringPrice;
			getline(stream, setNum, ',');
			getline(stream, legoTheme, ',');
			getline(stream, legoName, ',');
			getline(stream, stringMinifigs, ',');
			getline(stream, stringPieces, ',');
			getline(stream, stringPrice, ',');

			int minifigs, pieces;
			double _price;

			minifigs = stoi(stringMinifigs);
			pieces = stoi(stringPieces);
			_price = stod(stringPrice);

			lego newLego;
			newLego.setNumber = setNum;
			newLego.theme = legoTheme;
			newLego.setName = legoName;
			newLego.numPieces = pieces;
			newLego.numMinifigures = minifigs;
			newLego.price = _price;

			legos.push_back(newLego);
		}
	}

}
*/

struct movie {
	unsigned int budget;
	string company;
	string country;
	string director;
	string genre;
	unsigned int gross;
	string name;
	string rating;
	string releaseDate;
	int runtime;
	double score;
	string star;
	unsigned int votes;
	string writer; 
	int year;
};

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



	return 0;
}