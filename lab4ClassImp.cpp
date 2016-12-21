// lab4ClassImp.cpp 
// Implementation of the class 'Pokedex'
// November 20, 2016
// Author: Joseph Schell
// Sources: None

#include "lab4Header.h"

// Default Constructor
// Ensures proper initialization.
Pokedex::Pokedex() {
	count = 0;
	for (int i = 0; i < maxCreatures; i++) {
		creatures[i] = 0;
	}
}

// Destructor
// Ensures deletion of dynamic memory.
Pokedex::~Pokedex() {
	Pokemon * ptr;
	for (int i = 0; i < count; i++) {
		ptr = creatures[i];
		delete[] ptr->ability;
		delete[] ptr->name;
		delete[] ptr->type;
		delete ptr;
	}

	if (fileStr != NULL)
	{
		delete[] fileStr;
		fileStr = NULL;
	}
}

// Reads data from text file that was input
// by the user into pointer arrays.
int Pokedex::loadData() {
	fstream inputFile;
	char tempFileName[strSize], tempStr[strSize];
	char lastChar;
	long long charCount;

	cout << "What file would you like to use for input and output? ";
	cin.getline(tempFileName, strSize);

	int size = strlen(tempFileName); // added for set size to tempName
	fileStr = new char[size + 1]; // +1 for NULL
	strncpy(fileStr, tempFileName, size); // (destination, source, num)
	fileStr[size] = '\0'; // Explicit NULL termination
	inputFile.open(fileStr, ios::in);

	while (!inputFile.is_open()) {  // Invalid File Error Check
		cout << "File does not exist. Please try another file name: ";
		cin.getline(tempFileName, strSize);

		size = strlen(tempFileName);
		fileStr = new char[size + 1];
		strncpy(fileStr, tempFileName, size);
		fileStr[size] = '\0';
		inputFile.open(fileStr, ios::in);
	}
	inputFile.close();

	inputFile.open(fileStr, ios::in | ios::out);
	if (count < maxCreatures) {
		while (!inputFile.eof()) {
			Pokemon * ptr = new Pokemon;

			inputFile.getline(tempStr, strSize, ',');
			ptr->name = new char[strlen(tempStr) + 1]; // + 1 for null.
			strncpy(ptr->name, tempStr, strlen(tempStr) + 1);
			inputFile.getline(tempStr, strSize, ',');
			ptr->type = new char[strlen(tempStr) + 1]; // + 1 for null.
			strncpy(ptr->type, tempStr, strlen(tempStr) + 1);
			inputFile >> ptr->hitPoints;
			inputFile.ignore();
			inputFile >> ptr->attack;
			inputFile.ignore();
			inputFile >> ptr->defense;
			inputFile.ignore();
			inputFile.getline(tempStr, strSize, '\n');
			ptr->ability = new char[strlen(tempStr) + 1]; // + 1 for null.
			strncpy(ptr->ability, tempStr, strlen(tempStr) + 1);

			creatures[count] = ptr;
			count++;

			if (count >= maxCreatures) {
				break;
			}
		}
		// read end of file character
		inputFile.getline(tempStr, strSize, '\n');
	}

	// Check if last char in the file is \n. If not, then adds \n.
	inputFile.seekg(0, ios::end);
	charCount = inputFile.tellg();
	if (charCount > 0) {
		inputFile.seekg(-1, ios::end);
		lastChar = inputFile.peek();
		if (lastChar != '\n')
			inputFile.write("\n", 1);
	}
	inputFile.close();

	if (count >= maxCreatures) {   // Pokedex capacity check
		cout << "Successfully loaded " << count << " Pokemon, but the Pokedex is now full!" << endl;
	}
	else {
		cout << "Successfully loaded " << count << " Pokemon..." << endl;
	}
	displayData();
	return 0;
}

// Takes reply by user and executes the matching method.
void Pokedex::exeChoice(char reply) {
	switch (tolower(reply)) {
	case 'a':
		addPokemon();
		break;
	case 'l':
		displayData();
		break;
	case 's':
		searchByName();
		break;
	case 'm':
		findMaxHP();
		break;
	case 'q':
		writeData();
		break;
	default:
		cout << "Error, invalid input\n" << endl;
		break;
	}
}

// Displays all data from the database onto the screen.
void Pokedex::displayData() {
	cout << endl << left << setw(nameWidth) << "Name"
		<< left << setw(typeWidth) << "Type"
		<< left << setw(hpWidth) << "Hit Points"
		<< left << setw(atkWidth) << "Attack"
		<< left << setw(defWidth) << "Defense"
		<< left << setw(abilWidth) << "Ability" << endl;
	cout << "----------------------------------------"
		<< "----------------------------------------" << endl;
	for (int index = 0; index < count; index++) {
		cout << left << setw(nameWidth) << creatures[index]->name
			<< left << setw(typeWidth) << creatures[index]->type
			<< left << setw(hpWidth) << creatures[index]->hitPoints
			<< left << setw(atkWidth) << creatures[index]->attack
			<< left << setw(defWidth) << creatures[index]->defense
			<< left << setw(abilWidth) << creatures[index]->ability << endl;
	}
	cout << "\n";
}

// Takes user input and adds this data as a
// new creature to the database.
void Pokedex::addPokemon() {
	if (count < maxCreatures) {
		char tempStr[strSize];
		Pokemon * ptr = new Pokemon;

		readString(tempStr, "What is the name of the new creature? ");
		ptr->name = new char[strlen(tempStr) + 1];
		strncpy(ptr->name, tempStr, strlen(tempStr) + 1);
		readString(tempStr, "What is the type of this new creature? ");
		ptr->type = new char[strlen(tempStr) + 1];
		strncpy(ptr->type, tempStr, strlen(tempStr) + 1);
		ptr->hitPoints = readInt("How many hit points does this creature have? ");
		ptr->attack = readInt("What is the attack of this creature? ");
		ptr->defense = readInt("What is the defense of this creature? ");
		readString(tempStr, "What ability does this creature have? ");
		ptr->ability = new char[strlen(tempStr) + 1];
		strncpy(ptr->ability, tempStr, strlen(tempStr) + 1);

		cout << "\nSuccessfully added " << ptr->name << " to the pokedex.\n" << endl;

		creatures[count] = ptr;
		count++;
	}
	else {
		cout << "Cannot add anymore pokemon. Pokedex is full!\n" << endl;
	}
}

// Takes user input and tries to find a match
// inside of the database.
void Pokedex::searchByName() {
	char searchInput[strSize];
	int i;
	bool found = false;

	cout << "Which creature would you like to search for: ";
	cin.getline(searchInput, strSize);

	for (i = 0; i < count; i++) {
		if (strcmp(searchInput, creatures[i]->name) == 0) {
			cout << "The data for " << searchInput << " is as follows:" << endl;
			cout << "type: " << creatures[i]->type << ", hit points: " << creatures[i]->hitPoints
				<< ", attack: " << creatures[i]->attack << ", defense: " << creatures[i]->defense
				<< ", ability: " << creatures[i]->ability << "\n" << endl;
			found = true;
		}
	}
	if (found == false)
		cout << "I'm sorry, " << searchInput << " was not found in the pokedex.\n" << endl;
}

// Searches for a creature in the database
// that has the highest amount of HP.
void Pokedex::findMaxHP() {
	int i;
	int temp = 0;

	for (i = 0; i < count; i++) {
		if (creatures[i]->hitPoints > temp) {
			temp = creatures[i]->hitPoints;
		}
	}

	for (i = 0; i < count; i++) {
		if (temp == creatures[i]->hitPoints) {
			cout << "The creature with the max hit points is as follows: " << endl;
			cout << "Name: " << creatures[i]->name << ", type: " << creatures[i]->type
				<< ", hit points: " << creatures[i]->hitPoints << ", attack: "
				<< creatures[i]->attack << ", defense: " << creatures[i]->defense
				<< ", ability: " << creatures[i]->ability << "\n" << endl;
		}
	}
}

// Writes all data to the original text file.
void Pokedex::writeData() {
	ofstream outFile;
	outFile.open(fileStr, ios::in | ios::out);
	if (!outFile) {
		cout << "cannot open file to write new data!";
		exit(0);
	}

	for (int i = 0; i < count - 1; i++) {
		outFile << creatures[i]->name << ',' << creatures[i]->type << ','
			<< creatures[i]->hitPoints << ',' << creatures[i]->attack << ','
			<< creatures[i]->defense << ',' << creatures[i]->ability << '\n';
		//verifies last character written is '\n'
	}
	if (count > 0) {
		outFile << creatures[count - 1]->name << ','
			<< creatures[count - 1]->type << ','
			<< creatures[count - 1]->hitPoints << ','
			<< creatures[count - 1]->attack << ','
			<< creatures[count - 1]->defense << ','
			<< creatures[count - 1]->ability;
	}

	outFile.close();
	cout << "Successfully wrote creature data to the pokedex file." << endl;
	cout << "Terminating program..." << endl;
}