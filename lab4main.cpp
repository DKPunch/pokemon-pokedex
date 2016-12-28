// lab4main.cpp
// CS 162: Assignment 4 - Pokedex Database (Dynamic Memory Version)
// November 20, 2016
// Author: Joseph Schell
// Sources: None

#include "lab4Header.h"

int main() {
	Pokedex list;
	char reply;

	std::cout << "Welcome to the Pokemon collection program." << std::endl;
	list.loadData();

	do {
		std::cout << "What would you like to do: (L)ist, (A)dd, (S)earch, "
			<< "find (M)ax hit point creature, or (Q)uit: ";
		reply = readChoice();
		list.exeChoice(reply);
	} while (toupper(reply) != 'Q');

	system("pause");
	return 0;
}

// Reads user input into a char variable.
char readChoice() {
	char choice;

	std::cin >> choice;
	std::cin.ignore(100, '\n');
	return choice;
}

// Verifies user input is of data type 'int'.
int readInt(const char prompt[]) {
	int temp = 0;
	std::cout << prompt;
	std::cin >> temp;

	while (!std::cin) //Error Check
	{
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cout << "Invalid input! Try again!!\n";
		std::cin >> temp;
	}
	std::cin.ignore(100, '\n');
	return temp;
}

// Verifies user inputs c-string.
void readString(char inputStr[], const char prompt[]) {
	std::cout << prompt;
	std::cin.getline(inputStr, strSize, '\n');
	while (!std::cin) {
		std::cin.clear();
		std::cin.ignore(100, '\n');
	}
}
