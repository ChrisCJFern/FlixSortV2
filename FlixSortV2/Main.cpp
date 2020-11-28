#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits>
#include <ctype.h>
#include <unordered_map>
#include <map>
#include <random>

using namespace std;

class Random // Taken from given random number generator in COP3503
{
	// One instance of the x variable, and all instances SHARE this variable
	// static variables/functions exist for the lifetime of your program
	static std::mt19937 random;
public:
	static int x;
	// One and only one of this function
	// "this" doesn't exist in static functions b/c only one of the function
	// Can only access static variables within static functions
	static int Int(int min, int max) {
		std::uniform_int_distribution<int> dist(min, max);
		return dist(random);
	}
	static float Float(float min, float max) {
		std::uniform_real_distribution<float> dist(min, max);
		return dist(random);
	}
};

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

	movie() {
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
	}
	movie(unsigned int _budget, string _company, string _country, string _director, string _genre, unsigned int _gross, string _name,
		string _rating, string _releaseDate, int _runtime, double _score, string _star, int _votes, string _writer, int _year) {
		budget = _budget;
		company = _company;
		country = _country;
		director = _director;
		genre = _genre;
		gross = _gross;
		name = _name;
		rating = _rating;
		releaseDate = _releaseDate;
		runtime = _runtime;
		score = _score;
		star = _star;
		votes = _votes;
		writer = _writer;
		year = _year;
	}
};

int chooseGenre() {
	cin.clear();
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
		getline(cin, choice);
		if (choice == "0") {
			val = 0;
			chosen = true;
		}
		else {
			if (choice.length() != 1 || choice[0] < 'A' || (choice[0] < 'a' && choice[0] > 'Q') || choice[0] > 'q') {
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

int chooseYear() {
	string input;
	int choice = 0;
	bool chosen = false;
	cout << setfill('=') << setw(51);
	cout << "\n";
	cout << "|   Let's pick a range of years for your movie!  |" << endl;
	cout << "|      (a) 1986 - 1990      (e) 2006 - 2010      |" << endl;
	cout << "|      (b) 1991 - 1995      (f) 2011 - 2016      |" << endl;
	cout << "|      (c) 1996 - 2000      (g) All (1986-2016)  |" << endl;
	cout << "|      (d) 2001 - 2005                           |" << endl;
	cout << "|      (0) Enter 0 to Exit                       |" << endl;
	cout << setfill('=') << setw(51);
	cout << "\n";
	cout << "Please input the letter of the selected year: ";
	while (!chosen) {
		getline(cin, input);
		if (input == "0") {
			choice = 0;
			chosen = true;
		}
		else {
			if (input.length() != 1 || input[0] < 'A' || (input[0] < 'a' && input[0] > 'G') || input[0] > 'g') {
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
	return choice;
}

unordered_multimap<string, movie> createMap(string genre, int year1, int year2) {
	unordered_multimap<string, movie> m;              //https://www.cplusplus.com/reference/map/multimap/
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
	for (int i = 0; i < numLine; i++) {
		getline(movieFile, _budget, ',');
		char d;
		d = movieFile.get();
		if (char(d) == '"') {
			getline(movieFile, _company, '"');
			_company = _company.substr(0, _company.length() - 1);
			getline(movieFile, line, ',');
		}
		else {
			movieFile.putback(d);
			getline(movieFile, _company, ',');
		}
		getline(movieFile, _country, ',');
		getline(movieFile, _director, ',');
		getline(movieFile, _genre, ',');
		getline(movieFile, _gross, ',');
		d = movieFile.get();
		if (char(d) == '"') {
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
		movie temp(stoi(_budget), _company, _country, _director, _genre, stoi(_gross), _name, _rating, _released, stoi(_runtime),
			stod(_score), _star, stoi(_votes), _writer, stoi(_year));
		if (_genre == genre && (stoi(_year) >= year1) && (stoi(_year) <= year2)) {
			m.insert({ _name, temp });
		}
	}
	movieFile.close();
	return m;
}

unordered_multimap<string, movie> printMap(unordered_multimap<string, movie> m1) {
	auto iter = m1.begin();
	map<double, vector<movie>> m2;
	cout << m1.size() << endl;
	int ct = 1;
	for (iter; iter != m1.end(); iter++) {
		m2[(iter->second.score)].push_back(iter->second);
	}
	cout << m2.size() << endl;
	auto iter2 = m2.rbegin();								//https://www.geeksforgeeks.org/how-to-traverse-a-stl-map-in-reverse-direction/
	for (iter2; iter2 != m2.rend(); iter2++) {
		for (int i = 0; i < iter2->second.size(); i++) {
			cout << ct << ". " << iter2->second[i].name << " | " << iter2->second[i].director << " | " << iter2->second[i].runtime << " minutes" << endl;
			ct++;
		}
	}
	return m1;
}

vector<movie> marathon(double time, unordered_multimap<string, movie> m1) {
	vector<movie> v;
	auto iter = m1.begin();
	map<double, vector<movie>> m2;
	int ct = 1;
	for (iter; iter != m1.end(); iter++) {
		m2[(iter->second.runtime)].push_back(iter->second);
	}
	auto iter2 = m2.rbegin();
	for (iter2; iter2 != m2.rend(); iter2++) {
		if (iter2->first < time) {
			for (int i = 0; i < iter2->second.size(); i++) {
				if (iter2->second[i].runtime < time) {
					v.push_back(iter2->second[i]);
					time -= iter2->first;
				}
				else {
					break;
				}
			}
		}
	}
	return v;
}

int main() {
	unordered_map<int, string> genre = { {97, "Action"}, {98, "Adventure"}, {99, "Animation"}, {100, "Biography"}, {101, "Comedy"}, {102, "Crime"}, {103, "Drama"}, {104, "Family"}, {105, "Fantasy"}, {106, "Horror"}, {107, "Musical"}, {108, "Mystery"}, {109, "Romance"}, {110, "Sci-Fi"}, {111, "Thriller"}, {112, "War"}, {113, "Western"} };
	unordered_map<int, pair<int, int>> year = { {97, {1986, 1990}}, {98, {1991, 1995}}, {99, {1996, 2000}}, {100, {2001, 2005}}, {101, {2006, 2010}}, {102, {2011, 2016}}, {103, {1986, 2016}} };
	unordered_multimap<string, movie> m1;
	
	//---------------------PRINTS INITIAL MENU---------------------------------------
	cout << setfill('=') << setw(51);
	cout << "\n";
	cout << "|              Welcome to FlixSort               |" << endl;              //print once
	cout << "|     Est. 2020 by the Magical Movie Masters     |" << endl;
	cout << "|><><><><><><><><><><><><><><><><><><><><><><><><|" << endl;
	cout << "| Want to watch a movie marathon?                |" << endl;
	cout << "|   But can't decide what movie to watch         |" << endl;
	cout << "|      We can provide you with some options.     |" << endl;
	cout << "|><><><><><><><><><><><><><><><><><><><><><><><><|" << endl;
	cout << "|              Let's get started :)              |" << endl;

	string input;
	int choice;
	int choice2;
	string throwaway;
	do {
		double mins = 0.0;
		choice = chooseGenre();
		if (choice != 0) {
			choice2 = chooseYear();
			if (choice2 != 0) {
				cout << "Here is a list of " << genre[choice] << " movies from the year " << year[choice2].first << " to " << year[choice2].second << "." << endl;
				m1 = createMap(genre[choice], year[choice2].first, year[choice2].second);
				printMap(m1);
				/*cout << "How much time do you have? Enter in minutes: ";     //testing how to marathon?
				cin >> mins;
				vector<movie> movies;
				movies = marathon(mins, m1);
				for (int i = 1; i < movies.size()+1; i++) {
					cout << i << ". " << movies[i].name << " " << movies[i].runtime << endl;
				}*/
				cout << setfill('=') << setw(51);
				cout << "\n";
				cout << "|        Would you like to search again?         |" << endl;
				cout << setfill('=') << setw(51);
				cout << "\n";
				cout << "Enter Y or N: ";
				cin >> input;
				getline(cin, throwaway);
			}
			else {
				cout << "Goodbye!" << endl;
				input = "n";
			}
		}
		else {
			cout << "Goodbye!" << endl;
			input = "n";
		}
	} while (input == "Y" || input == "y");
	return 0;
}


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