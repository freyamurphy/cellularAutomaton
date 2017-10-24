#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

// Global variables
int width; // Number of elements in array
int height; // Number of rows in picture

bool* parent = new bool[width];
bool* child = new bool[width];

/* rule should always have size 8 since 2^3=8 (3 bits with 2 options each)*/
bool rule[8] = {0,0,0,1,1,1,1,0}; // Rule 30 (minimum requirement)

// Characters to output in picture
char char1 = '1';
char char2 = '0';

/* Gets the user to input the width of each line */
int getWidthOfLine()
{
	int w;
	cout<<"Please enter the width you would like the line to be: "<<endl;
	cin>>w;
	width = w;
	return w;
}
/* Gets the user to input the amount of rows */
int getAmountOfRows()
{
	int rows;
	cout<<"Please enter the amount of rows you would like: "<<endl;
	cin>>rows;
	height = rows;
	return rows;
}

// Set value of first row
void initParent() 
{
	bool bit;
	// Initialise random seed
	srand(time(NULL));
	
	for (int i = 0; i < width; i++)
	{
		// randomly choose 1 or 0
		bit = rand() % 2;
		parent[i] = bit;	
	}
}
/* Outputs the parent array */
void outputParent() {
	char outChar;
	for (int i = 0; i < width; i++) {
		if (parent[i]) {
			outChar = char1;
		}
		else {
			outChar = char2;
		}
		cout << outChar;
	}
}

// Calculate the contents of the child array based on the parent array
void calculateChild() {
	/*for (int i=0; i < width; i++) {
		cout << parent[i] << " ";
	}
	cout << endl;*/
	bool currentVal;
	bool prevVal;
	bool nextVal;
	// Loop through each cell in the row
	for (int i=0; i < width; i++) {
		currentVal = parent[i];
		
		// There is no previous cell for he first cell in the row.
		if (i <= 0) {
			// This is the part that will need changed for wrapping values around.
			prevVal = parent[width-1];
		} 
		else {
			prevVal = parent[i-1];
		}

		// The last cell in the array has no next cell.
		if (i >= width-1) {
			// This is the part that will need changed for wrapping values around.
			nextVal = parent[0];
		}
		else {
			nextVal = parent[i+1];
		}

		// Setting value of child row
		/* It might be more readable to use a switch statement but that requires combining 
		   the bool values into a string which is hard :(
		*/
		if (prevVal && currentVal && nextVal) {
			child[i] = rule[0];
		}
		else if (prevVal && currentVal && !nextVal) {
			child[i] = rule[1];
		}
		else if (prevVal && !currentVal && nextVal) {
			child[i] = rule[2];
		}
		else if (prevVal && !currentVal && !nextVal) {
			child[i] = rule[3];
		}
		else if (!prevVal && currentVal && nextVal) {
			child[i] = rule[4];
		}
		else if (!prevVal && currentVal && !nextVal) {
			child[i] = rule[5];
		}
		else if (!prevVal && !currentVal && nextVal) {
			child[i] = rule[6];
		}
		else {
			child[i] = rule[7];
		}
	}
}

void outputChild() {
	char outChar;
	for (int i = 0; i < width; i++) {
		if (child[i]) {
			outChar = char1;
		}
		else {
			outChar = char2;
		}
		cout << outChar;
	}
	cout << endl;
}


void copyChildToParent() {
	for (int i = 0; i < width; i++) {
		parent[i] = child[i];
	}
}

// Output text based picture by repeatedly calling calculateChildGen()
void outputPicture() {
	// Print first row
	outputParent();
	// Generate and print out child rows
	for (int i = 0; i < height; i++) {
		outputChild();
		// This child becomes the parent of the next row.
		copyChildToParent();
	}
}


int getRuleFromUser() {return 0;}

bool* convertDecimalToBinary(int decNum) {
	static bool binNum[8];
	int remainder;
	
	for (int i = 1; i < 9; i++) {
		remainder = decNum % 2;
		decNum /= 2;
		
		binNum[8 - i] = remainder;
	}
	for (int i = 0; i < 8; i++) {
		cout << binNum[i];
	}
	cout << endl;
	
	return binNum;
}

int convertBinaryToDecimal(int binNum) {return 0;}

bool* getRandomRule() {
	// This line is needed to make the numbers appear more random
	srand(time(NULL));
	// Choose random number from 0 to 256
	int decRule = rand() % 256;
	cout << "Rule " << decRule << endl;
	
	// Convert this rule to binary
	bool* binRule = convertDecimalToBinary(decRule);

	return binRule;
}

// Copy value of binRule into rule
void setRule(bool* binRule) {
	for (int i = 0; i < 8; i++) {
		rule[i] = binRule[i];
	}
}



void saveToFile() {}

void displayMenu(){}

int main() {
	cout << width << endl;
	getWidthOfLine();
	cout << width << endl;
	getAmountOfRows();
	initParent();
	//bool* binRule = getRandomRule();
	//setRule(binRule);
	outputPicture();
  return 0;
}
