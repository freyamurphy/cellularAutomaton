/* Based on final working version
   Try converting to vectors to work with dynamic width.
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

// Global variables
//int height = 35; // Number of rows in picture

/* Use vectors to store parent and child generations
   This allows the width to be changed.*/
vector<bool> parent;
vector<bool> child;

/* rule should always have size 8 since 2^3=8 (3 bits with 2 options each)*/
vector<bool> rule(8);

// Characters to output in picture
char char1 = '1';
char char2 = ' ';

// Get an integer from the user and return it
int getWidth() {
	int width;
	
	cout << "How many columns would you like in the picture?" << endl;
	cin >> width;
	
	// Input validation
	while (!cin || width <= 0) {
		cerr << "Invalid input." << endl;
		cout << "How many columns would you like in the picture?" << endl;
		
		// Clear the stream and try again.
		cin.clear();
		cin.ignore(1);
		cin >> width;
	}
	
	return width;
}

/* Get an integer from the user and return it */
int getHeight()
{
	int height;
	
	cout << "How many rows would you like in the picture?" << endl;
	cin >> height;
	
	// Input validation
	while (!cin || height <= 0) {
		cerr << "Invalid input." << endl;
		cout << "How many rows would you like in the picture?" << endl;
		
		// Clear the stream and try again.
		cin.clear();
		cin.ignore(1);
		cin >> height;
	}
	return height;
}

vector<bool> userGeneratedRow()
{
	//make width size of string no width variable 
	int userInput;
	vector<bool> userGeneratedRow;
	int width = getWidth();
	for(int i =0;i<width;i++)
	{
		cout<<"Please enter a 1 or a 0 and press 'Enter'"<<endl;
		cin>>userInput;
		userGeneratedRow.push_back(userInput);
	}
	return userGeneratedRow;
		
}

vector<bool> randomParentGeneration()
{
	// The next bit to add to the row
	bool bit;
	vector<bool> randomGeneration;
	int width = getWidth();
	// Initialise random seed
	srand(time(NULL));
		
	for (int i = 0; i < width; i++)
	{
		// randomly choose 1 or 0
		bit = rand() % 2;
		// Add bit to row
		randomGeneration.push_back(bit);
	} 
	return randomGeneration;
}

/* Set values of first row in picture
   mode="RANDOM" gives a randomly generated row
   mode="USER_INPUT" allows the user to enter the row
*/
void initParent()
{
	
	// Reset the row
	parent.clear();

	//Small menu for choosing how the parent is generated.
	int userInput;
	cout<<"Please choose from the following: "<<endl;
	cout<<"1. Use a randomly generated first row."<<endl;
	cout<<"2. Enter a first row."<<endl;
	cin>>userInput;
	switch(userInput)
	{
		case 1:	parent = randomParentGeneration();
			break;
		case 2: parent = userGeneratedRow();
			break;
	}
}

// Converts a decimal number to an 8 bit binary number
vector<bool> convertDecimalToBinary(int decNum) {
	// Vector to store rule in binary
	vector<bool> binNum(8);
	
	int remainder;
	
	// Repeatedly divide decNum by two and store remainder as binary digit
	for (int i = 1; i < binNum.size()+1; i++) {
		remainder = decNum % 2;
		decNum /= 2;
		
		if (binNum.size()-i >= 0) {
			binNum[binNum.size() - i] = remainder;
		}
	}
	
	return binNum;
}

// Convert an 8 bit binary number to a decimal value
int convertBinaryToDecimal(vector<bool> binNum) {
	int decNum = 0;
	int binDigit;
	int powerOfTwo = 1;
	
	for (int i = binNum.size()-1; i >= 0; i--) {
		binDigit = binNum.at(i);
		
		decNum += binDigit*powerOfTwo;
		
		// The power of 2 increases with each column
		powerOfTwo *= 2;
	}

	return decNum;
}

// Chooses a random rule from 0 to 256 and convert it to binary.
vector<bool> getRandomRule() {
	// This line is needed to make the numbers appear more random
	srand(time(NULL));
	
	// Choose random number from 0 to 256
	int decRule = rand() % 256;
	cout << "Rule " << decRule << endl;
	
	// Convert this rule to binary
	vector<bool> binRule = convertDecimalToBinary(decRule);

	return binRule;
}

/* Gets user to input their own rule in binary */
vector<bool> getUserRule()
{
	vector<bool> binRule;
	int usrInput;
	for(int i =0;i<8;i++)
	{
		cout<<"Please enter a 1 or a 0 and press 'Enter'"<<endl;
		cin>>usrInput;
		binRule.push_back(usrInput);
	}
	int decNum = convertBinaryToDecimal(binRule);
	cout<<"Rule" << decNum<<endl;
	return binRule;
}

/* Gets the user to input their own rule in decimals */
vector<bool> getUserDecRule()
{
	int userInput;
	vector<bool> decRule;
	cout<<"Please enter a decimal: "<<endl;
	cin>>userInput;
	cout<< "You have entered Rule "<< userInput<<endl;
	decRule = convertDecimalToBinary(userInput);
	return decRule;
}

/* Set value of rule vector
   mode="RANDOM" chooses a random rule
   mode="USER_BINARY" allows the user to enter a rule in binary
   mode="USER_DECIMAL" allows the user to enter a rule in decimal */
void setRule() {
	// Vector to store rule as binary number
	vector<bool> binRule(8);
	//use case statement for menu 
	int userInput;
	cout<<"Please choose from the following: "<<endl;
	cout<<"1. Use a random rule."<<endl;
	cout<<"2. Enter a rule in binary."<<endl;
	cout<<"3. Enter a rule in decimal."<<endl;
	cin>>userInput;
	switch(userInput)
	{
		case 1: binRule = getRandomRule();
			break;
		case 2: binRule = getUserRule();		
			break;					
		case 3:	binRule = getUserDecRule();
			break;
	}
	// Reset rule
	rule.clear();

	// Copy values into rule vector
	rule = binRule;
}

/* Calculates the contents of child row based on parent row
   mode="NO_WRAP" sets out of bounds neightbour cells to 0
   mode="WRAP" wraps cells around when calculating neighbours */
void calculateChild(string mode) {
	bool currentVal;
	bool prevVal;
	bool nextVal;
	
	// Reset child row
	child.clear();
	
	// Loop through each cell in the row
	for (int i=0; i < parent.size(); i++) {
		currentVal = parent.at(i);
		
		// There is no previous cell for the first cell in the row.
		if (i <= 0) {
			if (mode=="WRAP") {
				prevVal = parent.at(parent.size()-1);
			}
			else {
				prevVal = 0;
			}
		} 
		else {
			prevVal = parent.at(i-1);
		}

		// The last cell in the array has no next cell.
		if (i >= parent.size()-1) {
			if (mode=="WRAP") {
				nextVal = parent.at(0);
			}
			else {
				nextVal = 0;
			}
		}
		else {
			nextVal = parent.at(i+1);
		}

		// Setting value of child row
		if (prevVal && currentVal && nextVal) {
			child.push_back(rule.at(0));
		}
		else if (prevVal && currentVal && !nextVal) {
			child.push_back(rule.at(1));
		}
		else if (prevVal && !currentVal && nextVal) {
			child.push_back(rule.at(2));
		}
		else if (prevVal && !currentVal && !nextVal) {
			child.push_back(rule.at(3));
		}
		else if (!prevVal && currentVal && nextVal) {
			child.push_back(rule.at(4));
		}
		else if (!prevVal && currentVal && !nextVal) {
			child.push_back(rule.at(5));
		}
		else if (!prevVal && !currentVal && nextVal) {
			child.push_back(rule.at(6));
		}
		else {
			child.push_back(rule.at(7));
		}
	}
}

// Displays current value of parent row
void outputParent() {
	char outChar;
	for (int i = 0; i < parent.size(); i++) {
		if (parent.at(i)) {
			outChar = char1;
		}
		else {
			outChar = char2;
		}
		cout << outChar;
	}
	cout << endl;
}

// Displays current value of child row
void outputChild() {
	char outChar;
	for (int i = 0; i < child.size(); i++) {
		if (child.at(i)) {
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
	for (int i = 0; i < 10; i++) {
		parent[i] = child[i];
	}
}

// Output text based picture by repeatedly calling calculateChild()
void outputPicture() {
	
	int height = getHeight();
	// Print first row
	outputParent();
	
	// Generate and print out child rows
	for (int i = 0; i < height; i++){
		calculateChild("WRAP");
		outputChild();
		// This child becomes the parent of the next row.
		parent = child;
	}
}

void runProgram() {
	/* Code to get mode inputs from user needed here*/
	// Set rule from 0 to 255
	setRule();
	// Set first row of picture
	initParent();
	/* Draw picture
	   calculateChild("WRAP") is called within this function
	   need a way for user to set "WRAP" / "NO_WRAP" */
	outputPicture();
}

int main() {
	runProgram();
  	return 0;
}
