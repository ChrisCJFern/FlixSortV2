#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits>
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

vector<int> menuPrint() {
	cout << setfill('=') << setw(51);
	cout << "\n";
	cout << "|     How would you like to base your search?    |" << endl;
	cout << "|Enter the numbers of the choices you would like |" << endl;
	cout << "|to search by in the following format: # # # ..  |" << endl;
	cout << "|1. Time (in minutes)                            |" << endl;
	cout << "|2. Company                                      |" << endl;
	cout << "|3. Genre                                        |" << endl;
	cout << "|4. Rating                                       |" << endl;
	cout << "|5. Release year                                 |" << endl;
	cout << "|6. Director                                     |" << endl;
	cout << "|7. Starring actor/actress                       |" << endl;
	cout << setfill('=') << setw(51);
	cout << "\n";
	string choice;
	vector<int> choices;
	while (true) {
		cin >> choice;
		try {
			if (stoi(choice)) {
				int num = stoi(choice);
				if (find(choices.begin(), choices.end(), num) == choices.end()) {
					choices.push_back(num);
				}
			}
		}
		catch (const invalid_argument&) {
			cout << choice << " is an invalid input." << endl;
			cout << "Please enter your input in the format: # # #" << endl;
			choices.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');          //found information about cin.ignore() -> http://www.cplusplus.com/reference/istream/istream/ignore/
		}
		if (cin.peek() == '\n') {
			break;
		}
	}
	sort(choices.begin(), choices.end());
	return choices;
}


int main() {
	//---------------------PRINTS INITIAL MENU---------------------------------------
	cout << setfill('=') << setw(51);
	cout << "\n";
	cout << "|              Welcome to FlixSort               |" << endl;              //print once
	cout << "|     Est. 2020 by the Magical Movie Masters     |" << endl;
	cout << "|><><><><><><><><><><><><><><><><><><><><><><><><|" << endl;
	cout << "|1. Want to watch a movie marathon?              |" << endl;
	cout << "|2. Can't decide what movie to watch?            |" << endl;
	cout << "|             We can choose for you!             |" << endl;
	vector<int> choices;
	choices = menuPrint();
	for (int i = 0; i < choices.size(); i++) {
		cout << choices[i] << " ";
	}
	//------------------------SEARCH AGAIN---------------------------------------------
	cout << endl;
	cout << setfill('=') << setw(51);
	cout << "\n";
	cout << "|        Would you like to search again?         |" << endl;
	cout << "|                 Enter: Y or N                  |" << endl;
	cout << setfill('=') << setw(51);
	cout << "\n";
	string input;
	cin >> input;
	while (input == "Y" || input == "y") {
		choices = menuPrint();
		for (int i = 0; i < choices.size(); i++) {
			cout << choices[i] << " ";
		}
		cout << endl;
		cout << setfill('=') << setw(51);
		cout << "\n";
		cout << "|        Would you like to search again?         |" << endl;
		cout << "|                 Enter: Y or N                  |" << endl;
		cout << setfill('=') << setw(51);
		cout << "\n";
		cin >> input;
	}
	cout << "Enjoy the movie!" << endl;
	////////////////////////////////////////////////////////////////////////////////////

	string line;
	ifstream movieFile;
	movieFile.open("movies.csv", ios::in);
	while (movieFile.is_open()) {
		getline(movieFile, line);
		cout << line << endl;
	
	}
	movieFile.close();
	

	return 0;
}


