// lab4Header.h
// Header file for lab4ClassImp.cpp and lab4main.cpp
// November 20, 2016
// Author: Joseph Schell
// Sources: None

#ifndef _POKEDEX_
#define _POKEDEX_

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

// Global Constants
const int strSize = 200;
const int maxCreatures = 100;
const int nameWidth = 14;
const int typeWidth = 16;
const int hpWidth = 16;
const int atkWidth = 12;
const int defWidth = 14;
const int abilWidth = 20;

struct Pokemon {
	char  * name;
	char * type;
	int hitPoints;
	int attack;
	int defense;
	char * ability;
};

class Pokedex {
private:
	Pokemon * creatures[maxCreatures];
	int count;
public:
	Pokedex(); // Default Constructor
	~Pokedex(); // Destructor
	char * fileStr; // Array to store input file name.
	int loadData();
	void exeChoice(char reply);
	void displayData();
	void addPokemon();
	void searchByName();
	void findMaxHP();
	void writeData();
};

// Standard Function Prototypes
char readChoice();
int readInt(const char prompt[]);
void readString(char inputStr[], const char prompt[]);

#endif