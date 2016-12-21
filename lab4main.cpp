// lab4main.cpp
// CS 162: Assignment 4 - Pokedex Database (Dynamic Memory Version)
// November 20, 2016
// Author: Joseph Schell
// Sources: None

#include "lab4Header.h"

int main() {
	Pokedex list;
	char reply;

	cout << "Welcome to the Pokemon collection program." << endl;
	list.loadData();

	do {
		cout << "What would you like to do: (L)ist, (A)dd, (S)earch, "
			<< "find (M)ax hit point creature, or (Q)uit: ";
		reply = readChoice();
		list.exeChoice(reply);
	} while (toupper(reply) != 'Q');

	return 0;
}

// Reads user input into a char variable.
char readChoice() {
	char choice;

	cin >> choice;
	cin.ignore(100, '\n');
	return choice;
}

// Verifies user input is of data type 'int'.
int readInt(const char prompt[]) {
	int temp = 0;
	cout << prompt;
	cin >> temp;

	while (!cin) //Error Check
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Invalid input! Try again!!\n";
		cin >> temp;
	}
	cin.ignore(100, '\n');
	return temp;
}

// Verifies user inputs c-string.
void readString(char inputStr[], const char prompt[]) {
	cout << prompt;
	cin.getline(inputStr, strSize, '\n');
	while (!cin) {
		cin.clear();
		cin.ignore(100, '\n');
	}
}