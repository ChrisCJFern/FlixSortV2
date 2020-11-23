#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits>
#include <ctype.h>
#include <unordered_map>

using namespace std;

struct movie {
	unsigned int budget = 0;
	string company = "";
	string country = "";
	string director = "";
	string genre = "";
	unsigned int gross = 0;
	string name = "";
	string rating = "";
	string releaseDate = "";
	int runtime = 0;
	double score = 0.0;
	string star = "";
	int votes = 0;
	string writer = "";
	int year = 0;
};

int menuPrint() {
	cout << setfill('=') << setw(51);
	cout << "\n";
	cout << "|      What movie genre were you thinking?       |" << endl;
	cout << "|   (a) Action      (g) Drama     (m) Romance    |" << endl;
	cout << "|   (b) Adventure   (h) Family    (n) Sci-Fi     |" << endl;
	cout << "|   (c) Animation   (i) Fantasy   (o) Thriller   |" << endl;          //what genre are you thinking 
	cout << "|   (d) Biography   (j) Horror    (p) War        |" << endl;           //indexed list
	cout << "|   (e) Comedy      (k) Musical   (q) Western    |" << endl;
	cout << "|   (f) Crime       (l) Mystery                  |" << endl;
	cout << "|   (0) Enter 0 to Exit                          |" << endl;
	cout << setfill('=') << setw(51);
	cout << "\n";
	cout << "Please input the letter of the selected genre: ";
	string choice;
	bool chosen = false;
	int val = 0;
	while (!chosen) {
		cin >> choice;
		if (choice == "0") {
			val = 0;
			chosen = true;
		}
		else {
			if (choice.length() > 1 || choice.length() < 1 || choice[0] < 'A' || (choice[0] < 'a' && choice[0] > 'Q') ||  choice[0] > 'q') {
				cout << choice << " is an invalid input." << endl;
				cout << "Please enter your input in the correct format: ";
				choice.clear();
			}
			else {
				chosen = true;
				val = tolower(int(choice[0]));
				break;
			}
		}
	}
	return val;
}

bool runGenres(int choice) {
	switch (choice) {
		case 97:
			cout << "You chose Action." << endl;
			break;
		case 98:				
			cout << "You chose Adventure." << endl;
			break;
		case 99:
			cout << "You chose Animation." << endl;
			break;
		case 100:
			cout << "You chose Biography." << endl;
			break;
		case 101:
			cout << "You chose Comedy." << endl;
			break;
		case 102:
			cout << "You chose Crime." << endl;
			break;
		case 103:
			cout << "You chose Drama." << endl;
			break;
		case 104:
			cout << "You chose Family." << endl;
			break;
		case 105:
			cout << "You chose Fantasy." << endl;
			break;
		case 106:
			cout << "You chose Horror." << endl;
			break;
		case 107:
			cout << "You chose Musical." << endl;
			break;
		case 108:
			cout << "You chose Mystery." << endl;
			break;
		case 109:
			cout << "You chose Romance." << endl;
			break;
		case 110:
			cout << "You chose Sci-Fi." << endl;
			break;
		case 111:
			cout << "You chose Thriller." << endl;
			break;
		case 112:
			cout << "You chose War." << endl;
			break;
		case 113:
			cout << "You chose Western." << endl;
			break;
		case 0:
			cout << "Exiting now!" << endl;
			return false;
			break;
		default:
			cout << "..." << endl;
			break;
	}
	return true;
}
bool runYear() {
	string input;
	int choice = 0;
	bool chosen = false;
	cout << setfill('=') << setw(51);
	cout << "\n";
	cout << "|   Let's pick a range of years for your movie!  |" << endl;
	cout << "|      (a) 1986 - 1990      (d) 2001 - 2005      |" << endl;
	cout << "|      (b) 1991 - 1995      (e) 2005 - 2010      |" << endl;
	cout << "|      (c) 1996 - 2000      (f) 2011 - 2016      |" << endl;
	cout << "|      (0) Enter 0 to Exit                       |" << endl;
	cout << setfill('=') << setw(51);
	cout << "\n";
	cout << "Please input the letter of the selected year: ";
	while (!chosen) {
		cin >> input;
		if (input == "0") {
			choice = 0;
			chosen = true;
		}
		else {
			if (input.length() > 1 || input.length() < 1 || input[0] < 'A' || (input[0] < 'a' && input[0] > 'F') || input[0] > 'f') {
				cout << input << " is an invalid input." << endl;
				cout << "Please enter your input in the correct format: ";
				input.clear();
			}
			else {
				chosen = true;
				choice = tolower(int(input[0]));
				break;
			}
		}
	}
	switch (choice) {
	case 97:
		cout << "You chose 86-90." << endl;
		break;
	case 98:
		cout << "You chose 91-95." << endl;
		break;
	case 99:
		cout << "You chose 95-00." << endl;
		break;
	case 100:
		cout << "You chose 01-05." << endl;
		break;
	case 101:
		cout << "You chose 05-10." << endl;
		break;
	case 102:
		cout << "You chose 11-16." << endl;
		break;
	case 0:
		cout << "Exiting now!" << endl;
		return false;
		break;
	default:
		cout << "..." << endl;
		break;
	}
	return true;
}

void searchAgain() {
	string input;
	int choice;
	do {
		cout << setfill('=') << setw(51);
		cout << "\n";
		cout << "|        Would you like to search again?         |" << endl;
		cout << setfill('=') << setw(51);
		cout << "\n";
		cout << "Enter Y or N: ";
		cin >> input;
		if (input == "Y" || input == "y") {
			choice = menuPrint();
			if (runGenres(choice)) {
				if (runYear()) {
					searchAgain();
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}
	}
	while (input == "Y" || input == "y");
	cout << "Enjoy the movie!" << endl;
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
	cout << "|      We can provide you with some options.     |" << endl;
	cout << "|><><><><><><><><><><><><><><><><><><><><><><><><|" << endl;
	cout << "|              Let's get started :)              |" << endl;
	int choice = 0;
	choice = menuPrint();
	if (runGenres(choice)) {
		if (runYear()) {
			searchAgain();
		}
		else {
			cout << "Enjoy!" << endl;
		}
	}
	else {
		cout << "Ok goodbye!" << endl;
	}

	/*
	ok so i got bored and started to play around with the taking in info stuff and got all the parsing to work, need to figure out how to deal with duplicates...
	
	*/
	unordered_map<string, movie*> m;
	string line;
	ifstream movieFile;
	movieFile.open("movies.csv", ios::in);
	int numLine = 0;
	if (movieFile.is_open()) {
		getline(movieFile, line);
		while (getline(movieFile, line)) {
			numLine++;
		}
		movieFile.close();
	}
	string _budget, _company, _country, _director, _genre, _gross, _name, _rating;
	string _released, _runtime, _score, _star, _votes, _writer, _year;
	movieFile.open("movies.csv", ios::in);
	getline(movieFile, line);
	for (int i = 0; i < numLine-1; i++) {
		movie *temp = new movie();
		getline(movieFile, _budget, ',');
		char d; 
		d = movieFile.get();
		if (char(d) == '"') {
			getline(movieFile, _company, '"');
			_company = _company.substr(0, _company.length() - 1);
			getline(movieFile, line, ',');
		}
		else{
			movieFile.putback(d);
			getline(movieFile, _company, ',');
		}
		getline(movieFile, _country, ',');
		getline(movieFile, _director, ',');
		getline(movieFile, _genre, ',');
		getline(movieFile, _gross, ',');
		d = movieFile.get();
		if(char(d) == '"'){
			getline(movieFile, _name, '"');
			_name = _name.substr(0, _name.length() - 2);
			getline(movieFile, line, ',');
		}
		else {
			movieFile.putback(d);
			getline(movieFile, _name, ',');
		}		
		getline(movieFile, _rating, ',');
		getline(movieFile, _released, ',');
		getline(movieFile, _runtime, ',');
		getline(movieFile, _score, ',');
		getline(movieFile, _star, ',');
		getline(movieFile, _votes, ',');
		getline(movieFile, _writer, ',');
		getline(movieFile, _year);
		temp->budget = stoi(_budget);
		temp->company = _company;
		temp->country = _country;
		temp->director = _director;
		temp->genre = _genre;
		temp->gross = stoi(_gross);
		temp->name = _name;
		temp->rating = _rating;
		temp->releaseDate = _released;
		temp->runtime = stoi(_runtime);
		temp->score = stod(_score);
		temp->star = _star;
		temp->votes = stoi(_votes);
		temp->writer = _writer;
		temp->year = stoi(_year);
		m[_name] = temp;
	}
	movieFile.close();
	auto iter = m.begin();
	cout << m.size() << endl;
	for (iter; iter != m.end(); iter++) {
		cout << iter->second->name << endl;
	}
	return 0;
}

// AASFASAS


/*for (int i = 0; i < choices.size(); i++) {
	cout << choices[i] << ". ";
	switch (choices[i]) {
	case 1:
		cout << "How much time do you have? (in minutes)" << endl;
		break;
	case 2:
		cout << "Production Company" << endl;
					//list of options from a map or set?									//made into a method
		break;
	case 3:
		cout << "Genre: " << endl;
					//menu list of options from a set ?
		break;
	case 4:
		cout << "Rating" << endl;
		break;
	case 5:
		cout << "Release Year" << endl;
		break;
	case 6:
		cout << "Director" << endl;
		break;
	case 7:
		cout << "Starring actor" << endl;
		break;
	}
}*/
/*------------------------SEARCH AGAIN---------------------------------------------
//cout << endl;
cout << setfill('=') << setw(51);																		//made into function but here just in case
cout << "\n";
cout << "|        Would you like to search again?         |" << endl;
cout << "|                 Enter: Y or N                  |" << endl;
cout << setfill('=') << setw(51);
cout << "\n";
string input;
cin >> input;
while (input == "Y" || input == "y") {
	choices = menuPrint();
	runChoices(choices);
	cout << endl;
	cout << setfill('=') << setw(51);
	cout << "\n";
	cout << "|        Would you like to search again?         |" << endl;
	cout << "|                 Enter: Y or N                  |" << endl;
	cout << setfill('=') << setw(51);
	cout << "\n";
	cin >> input;
}
cout << "Enjoy the movie!" << endl;*/
////////////////////////////////////////////////////////////////////////////////////



//graph of genre to a vector of movie objects.

// genre's
// a. Action
// b. Adventure
// c. Animation
// d. Biography
// e. Comedy
// f. Crime
// g. Drama
// h. Family
// i. Fantasy
// j. Horror
// k. Musical
// l. Mystery
// m. Romance
// n. Sci-Fi
// o. Thriller
// p. War
// q. Western

/*

vector<int> menuPrint() {
	cout << setfill('=') << setw(51);
	cout << "\n";
	cout << "|     How would you like to base your search?    |" << endl;
	cout << "|Enter the numbers of the choices you would like |" << endl;
	cout << "|to search by in the following format: # # # ..  |" << endl;
	cout << "|1. Company                                      |" << endl;          //what genre are you thinking 
	cout << "|2. Genre                                        |" << endl;           //indexed list
	cout << "|3. Rating                                       |" << endl;
	cout << "|4. Release year (search by decade)              |" << endl;
	cout << "|5. Director                                     |" << endl;
	cout << "|6. Starring actor/actress                       |" << endl;
	cout << "|7. Exit                                         |" << endl;
	cout << setfill('=') << setw(51);
	cout << "\n";
	string choice;
	vector<int> choices;
	while (true) {
		cin >> choice;
		try {
			if (stoi(choice)) {
				int num = stoi(choice);
				if (num == 7) {
					choices.clear();
					choices.push_back(7);
					break;
				}
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

bool runChoices(vector<int> choices) {
	for (int i = 0; i < choices.size(); i++) {
		cout << choices[i] << ". ";
		switch (choices[i]) {
		case 1:
			cout << "hi";
			//cout << "How much time do you have? (in minutes)" << endl;
			break;
		case 1:
			cout << "Production Company" << endl;
			//list of options from a map or set?									//do methods for each here?
			break;
		case 2:
			cout << "Genre: " << endl;
			//menu list of options from a set ?
			break;
		case 3:
			cout << "Rating" << endl;
			break;
		case 4:
			cout << "Release Year" << endl;
			break;
		case 5:
			cout << "Director" << endl;
			break;
		case 7:
			cout << "goodbye" << endl;
			return false;
			break;
		default:
			cout << "===";
			break;
		}
	}
	return true;
}

void searchAgain() {
	string input;
	vector<int> choices;
	do {
		cout << setfill('=') << setw(51);
		cout << "\n";
		cout << "|        Would you like to search again?         |" << endl;
		cout << "|                 Enter: Y or N                  |" << endl;
		cout << setfill('=') << setw(51);
		cout << "\n";
		cin >> input;
		if (input == "Y" || input == "y") {
			choices = menuPrint();
			runChoices(choices);
		}
	} while (input == "Y" || input == "y");
	cout << "Enjoy the movie!" << endl;
}



cout << setfill('=') << setw(51);
	cout << "\n";
	cout << "|      What genre movie were you thinking?       |" << endl;
	cout << "|a. Action                                       |" << endl;
	cout << "|b. Adventure                                    |" << endl;
	cout << "|c. Animation                                    |" << endl;          //what genre are you thinking
	cout << "|d. Biography                                    |" << endl;           //indexed list
	cout << "|e. Comedy                                       |" << endl;
	cout << "|f. Crime                                        |" << endl;
	cout << "|g. Drama                                        |" << endl;
	cout << "|h. Family                                       |" << endl;
	cout << "|i. Fantasy                                      |" << endl;
	cout << "|j. Horror                                       |" << endl;
	cout << "|k. Musical                                      |" << endl;
	cout << "|l. Mystery                                      |" << endl;
	cout << "|m. Romance                                      |" << endl;
	cout << "|n. Sci-Fi                                       |" << endl;
	cout << "|o. Thriller                                     |" << endl;
	cout << "|p. War                                          |" << endl;
	cout << "|q. Western                                      |" << endl;
	cout << "|1. Exit                                         |" << endl;
	cout << setfill('=') << setw(51);
	cout << "\n";

	-------------------
	cout << setfill('=') << setw(51);
	cout << "\n";
	cout << "|      What genre movie were you thinking?       |" << endl;
	cout << "|   a. Action     b. Adventure   c. Animation    |" << endl;
	cout << "|   d. Biography  e. Comedy      f. Crime        |" << endl;
	cout << "|   g. Drama      h. Family      i. Fantasy      |" << endl;          //what genre are you thinking
	cout << "|   j. Horror     k. Musical     l. Mystery      |" << endl;           //indexed list
	cout << "|   m. Romance    n. Sci-Fi      o. Thriller     |" << endl;
	cout << "|   p. War        q. Western                     |" << endl;
	cout << "|1. Exit                                         |" << endl;
	cout << setfill('=') << setw(51);
	cout << "\n";
*/