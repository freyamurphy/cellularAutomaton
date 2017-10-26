// A header file for cellular automaton

// Get an integer from the user and return it
int getWidth();

/* Set values of first row in picture
   mode="RANDOM" gives a randomly generated row
   mode="USER_INPUT" allows the user to enter the row
*/
void initParent(string mode);

// Converts a decimal number to an 8 bit binary number
vector<bool> convertDecimalToBinary(int decNum);

// Convert an 8 bit binary number to a decimal value
int convertBinaryToDecimal(vector<bool> binNum);

// Chooses a random rule from 0 to 256 and convert it to binary.
vector<bool> getRandomRule();

/* Set value of rule vector
   mode="RANDOM" chooses a random rule
   mode="USER_BINARY" allows the user to enter a rule in binary
   mode="USER_DECIMAL" allows the user to enter a rule in decimal */
void setRule(string mode);

/* Calculates the contents of child row based on parent row
   mode="NO_WRAP" sets out of bounds neightbour cells to 0
   mode="WRAP" wraps cells around when calculating neighbours */
void calculateChild(string mode);

// Displays current value of parent row
void outputParent();

// Displays current value of child row
void outputChild();

// Output text based picture by repeatedly calling calculateChild()
void outputPicture();

void runProgram();
