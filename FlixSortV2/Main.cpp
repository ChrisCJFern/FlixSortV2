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
#include <ctime>
#include <chrono>
#include <queue>
#include <unordered_set>
#define TABLE_SIZE 6821
using namespace std;
using namespace std::chrono;

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
std::mt19937 Random::random(time(0)); // Static variables must be redeclared in global space

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

void minutesToHours(int minutes) {
	int hours = minutes / 60;
	minutes %= 60;
	if (hours > 1) {
		cout << hours << " hours ";
		if (minutes > 1) {
			cout << minutes << " minutes" << endl;
		}
		else {
			if (minutes != 0) {
				cout << minutes << " minute" << endl;
			}
			else {
				cout << endl;
			}
		}
	}
	else {
		cout << hours << " hour ";
		if (minutes > 1) {
			cout << minutes << " minutes" << endl;
		}
		else {
			if (minutes != 0) {
				cout << minutes << "minute" << endl;
			}
		}
	}
}

movie* selectRandomHelper(priority_queue<pair<int, movie*>> pq) {
	int randomIndex = Random::Int(0, pq.size() - 1); // Generate a random number
	int count = 0;
	while (count < randomIndex && !pq.empty()) {
		pq.pop();
		count++;
	}
	return pq.top().second;
}

void selectRandom(priority_queue<pair<int, movie*>> pq) {
	string input;
	string throwaway;
	cout << endl;
	movie* mov = selectRandomHelper(pq);
	cout << "Random Movie: " << mov->name << " | " << mov->company << " | " << mov->director << " | ";
	minutesToHours(mov->runtime);
	bool exit = false;
	int val = 0;
	while (!exit) {
		cout << setfill('=') << setw(51);
		cout << "\n";
		cout << "|      Would you like us to pick a different     |" << endl;
		cout << "|            random movie for you ?              |" << endl;
		cout << "|      (a) New Movie          (b) No thanks      |" << endl;
		cout << setfill('=') << setw(51);
		cout << "\n";
		cout << "Please enter the letter of your selected option: ";
		getline(cin, input);
		if (input.length() != 1 || input[0] < 'A' || (input[0] < 'a' && input[0] > 'B') || input[0] > 'b') {
			cout << input << " is an invalid input." << endl;
			cout << "Please enter your input in the correct format: ";
			input.clear();
		}
		else {
			if (tolower(input[0]) == 97) {
				cout << endl;
				movie* mov = selectRandomHelper(pq);
				cout << "Random Movie: " << mov->name << " | " << mov->company << " | " << mov->director << " | ";
				minutesToHours(mov->runtime);
			}
			else {
				exit = true;
			}
		}
	}
}

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

// chooses movies based on user's preferred rating PG, G 
int chooseRating() {
	cin.clear();
	cout << setfill('=') << setw(51);
	cout << "\n";
	cout << "|      What movie rating were you thinking?      |" << endl;
	cout << "|   (a) G               (f) NC-17                |" << endl;
	cout << "|   (b) PG / TV-PG      (g) Unrated/ Not rated   |" << endl;
	cout << "|   (c) PG-13 / TV-14   (h) B / B15              |" << endl;          //what genre are you thinking 
	cout << "|   (d) TV-MA           (i) Any rating           |" << endl;
	cout << "|   (e) R                                        |" << endl;
	cout << "|   (0) Enter 0 to Exit                          |" << endl;
	cout << setfill('=') << setw(51);
	cout << "\n";
	cout << "Please input the letter of the selected rating: ";
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
			if (choice.length() != 1 || choice[0] < 'A' || (choice[0] < 'a' && choice[0] > 'I') || choice[0] > 'i') {
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

int chooseOutput() {
	string input;
	int choice = 0;
	bool chosen = false;
	cout << setfill('=') << setw(51);
	cout << "\n";
	cout << "|   Which data structure would you like to use?  |" << endl;
	cout << "|      (a) Multimap            (c) Both          |" << endl;
	cout << "|      (b) Binary Search Tree  (0) Exit          |" << endl;
	cout << setfill('=') << setw(51);
	cout << "\n";
	cout << "Please input the letter of the selected structure: ";
	while (!chosen) {
		getline(cin, input);
		if (input == "0") {
			choice = 0;
			chosen = true;
		}
		else {
			if (input.length() != 1 || input[0] < 'A' || (input[0] < 'a' && input[0] > 'C') || input[0] > 'c') {
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

int chooseOption() {
	string input;
	int choice = 0;
	bool chosen = false;
	cout << setfill('=') << setw(51);
	cout << "\n";
	cout << "|          How would you like to continue?       |" << endl;
	cout << "| (a) Movie Marathon     (d) Save or View Movies |" << endl;
	cout << "| (b) Select Random      (0) Exit                |" << endl;
	cout << "| (c) Random & Marathon                          |" << endl;
	cout << setfill('=') << setw(51);
	cout << "\n";
	cout << "Please input the letter of the selected option: ";
	while (!chosen) {
		getline(cin, input);
		if (input == "0") {
			choice = 0;
			chosen = true;
		}
		else {
			if (input.length() != 1 || input[0] < 'A' || (input[0] < 'a' && input[0] > 'D') || input[0] > 'd') {
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

// creates a multimap based on user's preferences
unordered_multimap<string, movie> createMap(string genre, int year1, int year2, vector<string> ratings) {
	unordered_multimap<string, movie> m;              //https://www.cplusplus.com/reference/map/multimap/
	string line;
	ifstream movieFile;
	movieFile.open("movies.csv", ios::in);
	int numLine = 0;
	// checks how many lines are in the csv file
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
	// loop for the amount of lines in file
	for (int i = 0; i < numLine; i++) {
		// first take in the budget
		getline(movieFile, _budget, ',');
		// then the company name
		char d;
		d = movieFile.get();
		if (char(d) == '"') {
			getline(movieFile, _company, '"');
			_company = _company.substr(0, _company.length());
			getline(movieFile, line, ',');
		}
		else {
			movieFile.putback(d);
			getline(movieFile, _company, ',');
		}
		// then the country, director, genre, and gross
		getline(movieFile, _country, ',');
		getline(movieFile, _director, ',');
		getline(movieFile, _genre, ',');
		getline(movieFile, _gross, ',');
		// then the name
		d = movieFile.get();
		if (char(d) == '"') {
			getline(movieFile, _name, '"');
			_name = _name.substr(0, _name.length());
			getline(movieFile, line, ',');
		}
		else {
			movieFile.putback(d);
			getline(movieFile, _name, ',');
		}
		// then the rating, released date, runtime, score, star, votes, writer, year
		getline(movieFile, _rating, ',');
		getline(movieFile, _released, ',');
		getline(movieFile, _runtime, ',');
		getline(movieFile, _score, ',');
		getline(movieFile, _star, ',');
		getline(movieFile, _votes, ',');
		getline(movieFile, _writer, ',');
		getline(movieFile, _year);
		// adds values into movie structure
		movie temp(stoi(_budget), _company, _country, _director, _genre, stoi(_gross), _name, _rating, _released, stoi(_runtime),
			stod(_score), _star, stoi(_votes), _writer, stoi(_year));
		// only inserts movies based on the preferred genre and year range and rating
		if (_genre == genre && (stoi(_year) >= year1) && (stoi(_year) <= year2)) {
			if (ratings.size() == 0) {
				m.insert({ _name, temp });
			}
			else {
				for (int i = 0; i < ratings.size(); i++) {
					if (_rating == ratings[i]) {
						m.insert({ _name, temp });
					}
				}
			}
		}
	}
	movieFile.close();
	return m;
}

// prints the Map
void printMap(unordered_multimap<string, movie> m1) {
	auto iter = m1.begin();
	map<double, vector<movie*>> m2;
	int ct = 1;
	for (iter; iter != m1.end(); iter++) {
		m2[(iter->second.score)].push_back(&iter->second);
	}
	auto iter2 = m2.rbegin();								//https://www.geeksforgeeks.org/how-to-traverse-a-stl-map-in-reverse-direction/
	cout << "#. Movie | Company | Director | Runtime " << endl;
	for (iter2; iter2 != m2.rend(); iter2++) {
		for (int i = 0; i < iter2->second.size(); i++) {
			cout << ct << ". " << iter2->second[i]->name << " | " << iter2->second[i]->company << " | " << iter2->second[i]->director << " | ";
			minutesToHours(iter2->second[i]->runtime);
			ct++;
		}
	}
}

// AVL Tree
struct Node {
public:
	double val;
	movie name;
	Node* left;
	Node* right;
	int balancefactor = 0;
	Node() : val(0), name(), left(nullptr), right(nullptr) {}
	Node(double x, movie name1) : val(x), name(name1), left(nullptr), right(nullptr) {}
	Node(double x, movie name1, Node* left, Node* right) : val(x), name(name1), left(left), right(right) {}
};


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

Node* insertNameId(Node* node, movie name, double id) {                           //insert a node, by taking in a root node, a string for the name and an int for the id
	if (node == nullptr) {														//if node is nullptr, make a new node, else go to the left or right depending on how id compares to node value
		Node* temp = new Node(id, name);										//then set node's left or right equal to the result of calling insert on the node->left or node->right
		node = temp;
		return node;
		delete temp;
	}
	if (id <= node->val) {
		node->left = insertNameId(node->left, name, id);
	}
	else if (id > node->val) {
		node->right = insertNameId(node->right, name, id);
	}
	return balance(node);                                   //balance node and return resulting root
}

void recalcBalanceFactor(Node* node) {
	if (node) {
		calcBalanceFactor(node);
		calcBalanceFactor(node->left);
		calcBalanceFactor(node->right);
	}
}

//insert a node, by taking in a root node, a string for the name and an double for the rating out of 10
//if node is nullptr, make a new node, else go to the left or right depending on how id compares to node value
//then set node's left or right equal to the result of calling insert on the node->left or node->right
// inserts if year and genre match, if they do, add in rating/score value and movie name
Node* createTree(Node* tree, string genre, int year1, int year2, vector<string> ratings) {
	Node* root = nullptr;
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
			_company = _company.substr(0, _company.length());
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
			_name = _name.substr(0, _name.length());
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
			if (ratings.size() == 0) {
				root = insertNameId(root, temp, stod(_score));
			}
			else {
				for (int i = 0; i < ratings.size(); i++) {
					if (_rating == ratings[i]) {
						root = insertNameId(root, temp, stod(_score));
					}
				}
			}
		}
		if (i != 0) {
			recalcBalanceFactor(root);
		}
	}
	movieFile.close();
	return root;
}

// keeps count of movies in the tree
int count(int& ctr) {
	ctr++;
	return ctr - 1;
}

// prints movies in tree
void printInorder(Node* node, int& counter) {
	if (node == nullptr) {
		return;
	}
	else {
		printInorder(node->right, counter);
		cout << count(counter) << ". ";
		cout << node->name.name << " | " << node->name.company << " | " << node->name.director << " | ";
		minutesToHours(node->name.runtime);
		printInorder(node->left, counter);
	}
}

//convert multimap to priority queue for marathoning && random
void multimapToPQ(unordered_multimap<string, movie>& m1, priority_queue<pair<int, movie*>>& pq) {
	vector<movie> v;
	auto iter = m1.begin();
	for (iter; iter != m1.end(); iter++) {
		pq.push({ iter->second.runtime, &iter->second });
	}
}

void treeToPQ(Node* node, priority_queue<pair<int, movie*>>& pq) {
	if (node == nullptr) {
		return;
	}
	else {
		treeToPQ(node->left, pq);
		pq.push({ node->name.runtime, &node->name });
		treeToPQ(node->right, pq);
	}
}

// chooses movies for user to marathon randomly
priority_queue<pair<int,movie*>> randomMarathon(int mins, priority_queue<pair<int, movie*>> m1) {
	priority_queue<pair<int, movie*>> p;
	int time = 0;
	bool done = false;
	unordered_set<movie*> fit;
	unordered_set<movie*> toolong;

	while (!done) {
		movie* temp = selectRandomHelper(m1);
		if (fit.find(temp) == fit.end() && toolong.find(temp) == toolong.end()) {
			if (time + temp->runtime < mins ) {
				p.push({ temp->runtime,temp });
				time += temp->runtime;
				fit.insert(temp);
			}
			else {
				toolong.insert(temp);
			}
		}
		else {
			if (fit.size() == m1.size() || toolong.size() + fit.size() == m1.size()) {
				done = true;
			}
		}
	}
	return p;
}

// clears the priority queue
void clearPQ(priority_queue<pair<int, movie*>>& pq) {
	while (!pq.empty()) {
		pq.pop();
	}
}

// output for binge watching (marathoning) movies
void printMarathon(priority_queue<pair<int, movie*>>& m1) {
	string throwaway;
	//getline(cin, throwaway);
	bool output = false;
	bool exit = false;
	string hour;
	cout << setfill('=') << setw(51);
	cout << "\n";
	cout << "|      Your Personal Movie Marathon Planner      |" << endl;
	cout << setfill('=') << setw(51);
	cout << "\n";
	cout << "Enter the max number of hours: ";
	while (output == false) {
		cin >> hour;
		cout << endl;
		try {
			if (stod(hour)) {
				int mins = 60 * stod(hour);
				priority_queue<pair<int,movie*>> movies;
				movies = randomMarathon(mins, m1);
				int time = 0;
				int counter = 1;
				if(!movies.empty()){
					cout << "Here is a list of movies from longest to shortest runtime." << endl;
					while(!movies.empty()){
						cout << counter << ". " << movies.top().second->name << " | " << movies.top().second->company << " | " << movies.top().second->director << " | ";
						minutesToHours(movies.top().second->runtime);
						counter++;
						time += movies.top().second->runtime;
						movies.pop();
					}
					cout << "The total time it will take you to watch these movies is: ";
					minutesToHours(time);
					cout << endl;
				}
				else {
					cout << "No movies fit in your selected time frame." << endl;
				}
				output = true;
			}
			else if (hour == "0") {
				cout << "No movies fit in your selected time frame." << endl;
				output = true;
			}
		}
		catch (...) {
			output = false;
			cout << "Invalid input. Please enter a valid number: ";
		}
	}
	string input;
	cin.clear();
	while (!exit) {
		output = false;
		getline(cin, throwaway);
		cout << setfill('=') << setw(51);
		cout << "\n";
		cout << "|      Would you like us to pick a different     |" << endl;
		cout << "|           marathon series for you ?            |" << endl;
		cout << "|        (a) Yes           (b) No thanks         |" << endl;
		cout << setfill('=') << setw(51);
		cout << "\n";
		cout << "Please enter the letter of your selected option: ";
		getline(cin, input);
		if (input.length() != 1 || input[0] < 'A' || (input[0] < 'a' && input[0] > 'B') || input[0] > 'b') {
			cout << input << " is an invalid input." << endl;
			cout << "Please enter your input in the correct format: ";
			input.clear();
		}
		else {
			if (tolower(input[0]) == 97) {
				cout << "Enter the max number of hours: ";
				while (output == false) {
					cin >> hour;
					cout << endl;
					try {
						if (stod(hour)) {
							int mins = 60 * stod(hour);
							priority_queue<pair<int, movie*>> movies; 
							movies = randomMarathon(mins, m1);
							int time = 0;
							int counter = 1;
							if (!movies.empty()) {
								cout << "Here is a list of movies from longest to shortest runtime." << endl;
								while (!movies.empty()) {
									cout << counter << ". " << movies.top().second->name << " | " << movies.top().second->company << " | " << movies.top().second->director << " | ";
									minutesToHours(movies.top().second->runtime);
									counter++;
									time += movies.top().second->runtime;
									movies.pop();
								}
								cout << "The total time it will take you to watch these movies is: ";
								minutesToHours(time);
								cout << endl;
							}
							else {
								cout << "No movies fit in your selected time frame." << endl;
							}
							output = true;
						}
						else if (hour == "0") {
							cout << "No movies fit in your selected time frame." << endl;
							output = true;
						}
					}
					catch (...) {
						output = false;
						cout << "Invalid input. Please enter a valid number: ";
					}
				}
			}
			else {
				exit = true;
			}
		}
	}
}

vector<movie> saveMovie(unordered_multimap<string, movie> m1, vector<movie>& movieSaves) {
	// menu to store or show list of movies
	int movieFound = 0;
	bool chosen = false;
	string input;
	while (!chosen) {
		string option = "";
		cout << endl;
		cout << setfill('=') << setw(71);
		cout << "\n";
		cout << "| Would you like to store a movie or show your list of saved movies? |" << endl;
		cout << "|          (a) Store a movie     (b) Show list of saved movies       |" << endl;
		cout << setfill('=') << setw(71);
		cout << "\n";
		cout << "Please input the letter of the selected option: ";
		getline(cin, option);
		// store movie
		if (option == "a") {
			while (movieFound == 0) {
				cout << "What movie would you like to store?: ";
				getline(cin, input);
				for (auto iter = m1.begin(); iter != m1.end(); ++iter) {
					// if movie is found in list
					if (input == iter->first) {
						movieSaves.push_back(iter->second);
						movieFound = 1;
						cout << input << " has been successfully saved!" << endl << endl;
					}
				}
				// if movie was not found in the list
				if (movieFound == 0) {
					cout << input << " was not found. Try again. " << endl << endl;
				}
			}
		}
		else if (option == "b") {
			// if the list of movies is empty
			if (movieSaves.size() <= 0) {
				cout << "You have not saved any movies." << endl << endl;
			}
			else {
				// cout the list of saved movies
				for (auto iter = movieSaves.begin(); iter != movieSaves.end(); ++iter) {
					cout << iter->name << " | " << iter->company << " | " << iter->director << " | ";
					minutesToHours(iter->runtime);
					cout << endl;
				}
			}
		}
		else { // if input is invalid
			cout << "invalid input" << endl << endl;
		}
		string option2 = "";
		cout << setfill('=') << setw(74);
		cout << "\n";
		cout << "|Would you like to continue or add more movies/look at saved movie list?|" << endl;
		cout << "|                 (a) Continue               (b) Repeat                 |" << endl;
		cout << setfill('=') << setw(74);
		cout << "\n";
		cout << "Please input the letter of the selected option: ";
		getline(cin, option2);
		if (option2 == "a") { chosen = true; }
	}
	

	return movieSaves;
}

int main() {
	unordered_map<int, string> genre = { {97, "Action"}, {98, "Adventure"}, {99, "Animation"}, {100, "Biography"}, {101, "Comedy"}, {102, "Crime"}, {103, "Drama"}, {104, "Family"}, {105, "Fantasy"}, {106, "Horror"}, {107, "Musical"}, {108, "Mystery"}, {109, "Romance"}, {110, "Sci-Fi"}, {111, "Thriller"}, {112, "War"}, {113, "Western"} };
	unordered_map<int, vector<string>> rating = { {97, {"G"}}, {98, {"PG", "TV-PG"}}, {99, {"PG-13", "TV-14"}}, {100, {"TV-MA"}}, {101, {"R"}}, {102, {"NC-17"}}, { 103, {"UNRATED", "NOT RATED", "Not specified"}}, { 104, {"B", "B15"}}, {105, {}} };
	unordered_map<int, pair<int, int>> year = { {97, {1986, 1990}}, {98, {1991, 1995}}, {99, {1996, 2000}}, {100, {2001, 2005}}, {101, {2006, 2010}}, {102, {2011, 2016}}, {103, {1986, 2016}} };
	unordered_multimap<string, movie> m1;
	vector<movie> movieSaves;
	Node* tree = new Node();

	//---------------------PRINTS INITIAL MENU---------------------------------------
	cout << setfill('=') << setw(51);
	cout << "\n";
	cout << "|              Welcome to FlixSort               |" << endl;              //print once
	cout << "|     Est. 2020 by the Magical Movie Masters     |" << endl;
	cout << "|><><><><><><><><><><><><><><><><><><><><><><><><|" << endl;
	cout << "| Want to watch a movie marathon?                |" << endl;
	cout << "|   But can't decide what movie to watch.        |" << endl;
	cout << "|      We can provide you with some options.     |" << endl;
	cout << "|><><><><><><><><><><><><><><><><><><><><><><><><|" << endl;
	cout << "|              Let's get started :)              |" << endl;

	string input;
	int choice;
	int choice2;
	int choice3;
	int choice4;
	string throwaway;
	priority_queue<pair<int, movie*>> m;
	int count = 1;
	do {
		double mins = 0.0;
		choice = chooseGenre();
		if (choice != 0) {
			choice2 = chooseYear();
			if (choice2 != 0) {
				choice3 = chooseRating();
				if (choice3 != 0) {
					choice4 = chooseOutput();
					if (choice4 != 0) {
						// if user wants to print movies from map
						if (choice4 == 97) { // 97 = 'a'
							cout << endl;
							auto startMap = high_resolution_clock::now();
							// prints out map options
							m1 = createMap(genre[choice], year[choice2].first, year[choice2].second, rating[choice3]);
							if (m1.size() != 0) {
								cout << "Here is a list of " << genre[choice] << " movies from the year " << year[choice2].first << " to " << year[choice2].second << "." << endl;
								printMap(m1);
								auto stopMap = high_resolution_clock::now();
								auto durationMap = duration_cast<microseconds>(stopMap - startMap);
								cout << "\n" << "Time taken to create and print the map: " << durationMap.count() << " microseconds" << endl;
								multimapToPQ(m1, m);
							}
							else {
								cout << "There are no movies that fit your selections." << endl;
							}
						}
						// if user wants to print movies from tree
						else if (choice4 == 98) {
							auto startTree = high_resolution_clock::now();
							// prints out tree options
							tree = createTree(tree, genre[choice], year[choice2].first, year[choice2].second, rating[choice3]);
							if (tree != nullptr) {
								cout << "Here is a list of " << genre[choice] << " movies from the year " << year[choice2].first << " to " << year[choice2].second << "." << endl;
								cout << "#. Movie | Company | Director | Runtime " << endl;
								printInorder(tree, count);
								auto stopTree = high_resolution_clock::now();
								auto durationTree = duration_cast<microseconds>(stopTree - startTree);
								cout << "\n" << "Time taken to create and print the tree: " << durationTree.count() << " microseconds" << endl;
								treeToPQ(tree, m);
							}
							else {
								cout << "There are no movies that fit your selections." << endl;
							}
						}
						// if user wants to print movies from map and tree
						else {
							auto startMap = high_resolution_clock::now();
							// prints out map options
							m1 = createMap(genre[choice], year[choice2].first, year[choice2].second, rating[choice3]);
							if (m1.size() != 0) {
								cout << "Here is a list of " << genre[choice] << " movies from the year " << year[choice2].first << " to " << year[choice2].second << "." << endl;
								cout << "Movies from the map: " << endl;
								printMap(m1);
								auto stopMap = high_resolution_clock::now();
								auto durationMap = duration_cast<microseconds>(stopMap - startMap);
								auto startTree = high_resolution_clock::now();
								// prints out tree options
								cout << endl;
								cout << "Movies from the Binary Search AVL tree: " << endl;
								cout << "#. Movie | Company | Director | Runtime " << endl;
								tree = createTree(tree, genre[choice], year[choice2].first, year[choice2].second, rating[choice3]);
								printInorder(tree, count);
								auto stopTree = high_resolution_clock::now();
								auto durationTree = duration_cast<microseconds>(stopTree - startTree);
								auto timeDiff = duration_cast<microseconds>(durationTree - durationMap);
								// outputs times
								cout << endl << "Time stats: " << endl;
								cout << "Time taken to create and print the map: " << durationMap.count() << " microseconds" << endl;
								cout << "Time taken to create and print the tree: " << durationTree.count() << " microseconds" << endl;
								if (timeDiff.count() > 0) { // if map was faster
									cout << "It was " << timeDiff.count() << " microseconds faster to use a map than to use a tree." << endl;
								}
								else if (timeDiff.count() < 0) { // if tree was faster
									cout << "It was " << abs(timeDiff.count()) << " microseconds faster to use a tree than to use a map." << endl;
								}
								else { // if both took the same amount of time
									cout << "Both the tree and map took the same amount of time to create and print." << endl;
								}
								multimapToPQ(m1, m);
							}
							else {
								cout << "There are no movies that fit your selections." << endl;
							}
						}

						if (!m.empty()) {
							int choice5 = chooseOption();
							if (choice5 != 0) {
								switch (choice5) {
								case 97:
									printMarathon(m);
									break;
								case 98:
									selectRandom(m);
									break;
								case 99:
									selectRandom(m);
									printMarathon(m);
									break;
								case 100:
									m1 = createMap(genre[choice], year[choice2].first, year[choice2].second, rating[choice3]);
									saveMovie(m1, movieSaves);
									break;
								default:
									break;
								}
							}
							else {
								input = "n";
							}
						}
						if (input != "n") {
							cout << setfill('=') << setw(51);
							cout << "\n";
							cout << "|   Would you like to start your search again?   |" << endl;
							cout << setfill('=') << setw(51);
							cout << "\n";
							cout << "Enter Y or N: ";
							cin >> input;
							m1.clear();
							clearPQ(m);
							tree = nullptr;
							getline(cin, throwaway);
						}
					}
					else {
						input = "n";
					}
				}
				else {
					input = "n";
				}
			}
			else {
				input = "n";
			}
		}
		else {
			input = "n";
		}
	} while (input == "Y" || input == "y");
	cout << "Goodbye!" << endl;

	return 0;
}
