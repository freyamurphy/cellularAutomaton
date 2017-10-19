#include <iostream>
#include <string>

using namespace std;

// Global variables
int width = 8; // Number of elements in array (current implementation only works for width=8)
int height = 8; // Number of rows in picture

// [8] should be replaced with [width] but need to figure out how to make this work.
bool parent[8] = {0,0,0,1,0,0,0,0};
bool child[8];
/* rule should always have size 8 since 2^3=8 (3 bits with 2 options each)*/
bool rule[8] = {0,0,0,1,1,1,1,0}; // Rule 30 (minimum requirement)

// Characters to output in picture
char char1 = '1';
char char2 = ' ';

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
		calculateChild();
		outputChild();
		// This child becomes the parent of the next row.
		copyChildToParent();
	}
}

void getWidth() {

}

void getHeight() {

}

int main() {
	outputPicture();
  return 0;
}
