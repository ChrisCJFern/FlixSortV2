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

/*
class Random // Taken from given random number generator in COP3503 //MAYBE FOR RANDOM MOVIE SELECTOR
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
*/

// movie structure
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

	// default constructor
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
	// constructor
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

// chooses movies based on user's preferred genre
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

// chooses movies based on user's preferred year range
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

// creates a multimap based on user's preferences with greatest to lowest rank
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

// prints the Map
void printMap(unordered_multimap<string, movie> m1) {
	auto iter = m1.begin();
	map<double, vector<movie>> m2;
	cout << m1.size() << endl; // For debugging purposes
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

vector<movie> createMovieVector(double time, unordered_multimap<string, movie> m1) {
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
				v.push_back(iter2->second[i]);
				time -= iter2->first;
			}
		}
	}
	return v;
}
// AVL Tree

struct Node {
public:
	int val;
	string name;
	Node* left;
	Node* right;
	int balancefactor = 0;
	Node() : val(0), name(""), left(nullptr), right(nullptr) {}
	Node(int x, string name1) : val(x), name(name1), left(nullptr), right(nullptr) {}
	Node(int x, string name1, Node* left, Node* right) : val(x), name(name1), left(left), right(right) {}
};

Node* insertNameId(Node* node, string name, int id) {                           //insert a node, by taking in a root node, a string for the name and an int for the id
	if (node == nullptr) {														//if node is nullptr, make a new node, else go to the left or right depending on how id compares to node value
		Node* temp = new Node(id, name);										//then set node's left or right equal to the result of calling insert on the node->left or node->right
		node = temp;
		return node;
		delete temp;
	}
	if (id < node->val) {
		node->left = insertNameId(node->left, name, id);
	}
	else if (id > node->val) {
		node->right = insertNameId(node->right, name, id);
	}
	return balance(node);                                   //balance node and return resulting root
}

Node* rotateLeft(Node* node) {
	Node* grandchild = node->right->left;
	Node* newParent = node->right;
	node->right = grandchild;
	newParent->left = node;
	return newParent;
}

//right rotation on node
Node* rotateRight(Node* node) {
	Node* grandchild = node->left->right;
	Node* newParent = node->left;
	node->left = grandchild;
	newParent->right = node;
	return newParent;
}

//left right rotation on node
Node* rotateLeftRight(Node* node) {
	node->left = rotateLeft(node->left);
	return rotateRight(node);
}

//right left rotation on node
Node* rotateRightLeft(Node* node) {
	node->right = rotateRight(node->right);
	return rotateLeft(node);
}


//calculate the left height of a node by adding one for every 
//left node that exists and do the same for the right side
//return the max of the left or right value 
int height(Node* node) {
	if (node == nullptr) {
		return 0;
	}
	if (node->left == nullptr && node->right == nullptr) {
		return 1;
	}
	else {
		int leftHeight = 1 + height(node->left);
		int rightHeight = 1 + height(node->right);
		if (leftHeight >= rightHeight) {
			return leftHeight;
		}
		else {
			return rightHeight;
		}
	}
}

//calculate the balance factor of a node by
// calling the height function on node->left and node->right 
// and taking the difference of left - right
int calcBalanceFactor(Node* node) {
	if (node == nullptr) {
		return 0;
	}
	if (node->left == nullptr && node->right == nullptr) {
		return 0;
	}
	else {
		int left = height(node->left);
		int right = height(node->right);
		int balance = left - right;
		node->balancefactor = balance;
		return balance;
	}
}

Node* balance(Node* node) {
	//find the correct rotation to implement on the inputted node
	node->balancefactor = calcBalanceFactor(node);
	if (node->balancefactor > 1) {
		node->left->balancefactor = calcBalanceFactor(node->left);
		//if both balance factor of node and node->left are (+), do a right rotation
		if (node->left->balancefactor > 0) {
			return rotateRight(node);
		}
		//if balance factor of node is (+) and node->left is (-), do a left right rotation
		else if (node->left->balancefactor < 0) {
			return rotateLeftRight(node);
		}
	}
	if (node->balancefactor < -1) {
		node->right->balancefactor = calcBalanceFactor(node->right);
		//if balance factors of node and node->right are (-), do a left rotation
		if (node->right->balancefactor < 0) {
			return rotateLeft(node);
		}
		//if balance factor of node is (-) and node->right is (+), do a right left rotation
		else if (node->right->balancefactor > 0) {
			return rotateRightLeft(node);
		}
	}
	return node;
}

void recalcBalanceFactor(Node* node) {
	if (node) {
		calcBalanceFactor(node);
		calcBalanceFactor(node->left);
		calcBalanceFactor(node->right);
	}
}

//root = insertNameId(root, name, id);
//recalcBalanceFactor(root);


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
