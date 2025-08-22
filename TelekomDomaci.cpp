// TelekomDomaci.cpp

#include <iostream>
#include <cmath>

//Gets the length of the coded word
int getCodedLength(){
    int input;
    std::cout << "Enter the length of the coded word: ";
    std::cin >> input;
    return input;
}

//Gets the parity bit
char getParityBit() {
    char input;
    std::cout << "\nDo you want a parity bit? [y/n]";
    std::cin >> input;
    return input;
}

//Checks if the provided code length is correct and if the parity response is correct
bool checkInputConditions(int codedLength, char parityChar) {
    if (!(parityChar == 'y' || parityChar == 'n')) {
        std::cout << "Unsupported answer for parity bit.";
        return 2;
    }
    if (codedLength > 31 || codedLength <= 2 || ((codedLength == 3 || codedLength == 4) && parityChar == 'y')) {
        std::cout << "Provided code length isn't supported.";
        return 1;
    }
    return 0;
}

//Gets the information word
std::string getInformationWord() {
    std::string input;
    std::cout << "Enter the information word (in binary format): ";
    std::cin >> input;
    return input;
}

//Checks whether the provided information word is of correct length and if it is a binary number
bool checkInformationWord(std::string& providedInformationWord, int informationLength) {

    if (providedInformationWord.length() != informationLength) {
        std::cout << "The provided word isn't the correct length. Provided: " << providedInformationWord.length() << " Required: " << informationLength << std::endl;
        return 1;
    }

    bool notBinary = false;

    for (int i = 0; i < providedInformationWord.length(); i++) {

        if (!(providedInformationWord[i] == '0' || providedInformationWord[i] == '1'))notBinary = true;
    }
    if (notBinary) {
        std::cout << "You must enter a binary number.";
        return 2;
    }
    return 0;
}

//Gets the changed bit
int getChangedBit() {
    int changedBit;
    std::cout << "Enter the changed bit position: ";
    std::cin >> changedBit;
    return changedBit;
}

//Checks if the provided changed bit position is out of range for the coded word
bool checkChangedBit(int changedBitPos, int codedLength) {
    if (changedBitPos > codedLength || changedBitPos <= 0) {
        std::cout << "The provided bit position is out of bounds. Provided: " << changedBitPos << " Bounds: " << 1 << "-" << codedLength << std::endl;
        return 1;
    }
    return 0;
}

//Checks whether x is a power of two or not
bool isPowerOfTwo(int x) {
    return (x & (x - 1)) == 0;
}

//Calculates the coded word from the information word
std::string encodeInformationWord(std::string& informationWord, int codedLength, int controlLength, bool parityBit) {
    std::string codedWord = std::string(codedLength, '0');

    //Writing the information bits into the coded word
    int j = 0;
    for (int i = 0; i < codedLength && j < informationWord.size(); i++) {
        if (!isPowerOfTwo(i + 1)) {
            codedWord[i] = informationWord[j++];
        }
    }

    //Calculating the control bits and writing them into the coded word
    for (int i = 0; i < controlLength - parityBit; i++) {
        int controlPosition = 1 << i; // control bit position (1-based)

        int control = 0;
        for (int j = 1; j <= codedLength; ++j) {
            if (j & controlPosition) {
                control ^= (codedWord[j - 1] == '1');
            }
        }

        codedWord[controlPosition - 1] = control + '0';
    }
    //Calculating the control bit if it was enabled
    if (parityBit) {
        int control = 0;
        for (int i = 0; i < codedLength - 1; i++) {
            control ^= (codedWord[i] == '1');
        }
        codedWord[codedLength - 1] = control + '0';
    }

    return codedWord;
}

//Flips the bit of a specified position
void alterBit(std::string& word, int pos) {
    if (word[pos - 1] == '1') word[pos - 1] = '0';
    else word[pos - 1] = '1';
}

//Calculates the control sum for the received coded word
int calculateControlSum(std::string& codedWord, int codedLength, int controlLength, bool parityBit) {
    int controlSum = 0;
    for (int i = 0; i < controlLength - parityBit; i++) {
        int controlPosition = 1 << i;

        int control = 0;
        for (int j = 1; j <= codedLength; ++j) {
            if (j & controlPosition) {
                control ^= (codedWord[j - 1] == '1');
            }
        }

        controlSum ^= control << i;
    }
    return controlSum;
}

//Calculates the parity sum for the received coded word
int calculateParitySum(std::string& codedWord, int codedLength, bool parityBit) {
    int paritySum = 0;
    if (parityBit) {
        for (int j = 1; j <= codedLength; ++j) {
            paritySum ^= (codedWord[j - 1] == '1');
        }
    }
    return paritySum;
}

//Decodes the coded word into the information word
std::string decodeInformationWord(std::string& codedWord, int codedLength, bool parityBit) {
    std::string receivedInformationWord = "";
    for (int i = 0; i < codedLength - parityBit; i++) {
        if (i != 0 && i != 1 && i != 3 && i != 7 && i != 15) {
            receivedInformationWord += codedWord[i];
        }
    }
    return receivedInformationWord;
}

int main()
{
    int codedLen;
    int informationLen;
    int controlLen;
    bool parityBit;
    std::string informationWord;
    std::string receivedInformationWord = "";
    std::string codedWord;
    std::string receivedCodedWord;
    int changedBit;
    
    //Reading the coded word length and whether the parity bit is enabled
    codedLen = getCodedLength();
    char parityChar = getParityBit();

    if (checkInputConditions(codedLen, parityChar)) {
        return -1;
    }
    parityBit = (parityChar == 'y');

    //calculating the number of control bits and the length of the information word
    controlLen = std::ceil(std::log2(codedLen + 1 - parityBit)) + parityBit;

    informationLen = codedLen - controlLen;

    std::cout << "Coded word length:" << codedLen << "\nInformation word length: " << informationLen << std::endl << std::endl;

    while (true) {

        //Reading the information word
        informationWord = getInformationWord();
        
        if (checkInformationWord(informationWord, informationLen) > 0) continue;

        //Reading the changed bit position
        changedBit = getChangedBit();

        if (checkChangedBit(changedBit, codedLen)) continue;

        //Encoding the information word into a coded word with control bits
        codedWord = encodeInformationWord(informationWord, codedLen, controlLen, parityBit);
        
        std::cout << "Sent information word: " << informationWord << "\n";
        std::cout << "Sent coded word: " << codedWord << "\n";


        //Adding the error on the provided bit position
        receivedCodedWord = codedWord;
        alterBit(receivedCodedWord, changedBit);
        
        std::cout << "Received coded word: " << receivedCodedWord << "\n";

        //Calculating the control sums
        int controlSum = calculateControlSum(receivedCodedWord, codedLen, controlLen, parityBit);
        int paritySum = calculateParitySum(receivedCodedWord, codedLen, parityBit);

        std::cout << "Control sum: " << controlSum << std::endl;
        std::cout << "Parity sum: " << paritySum << std::endl;

        //Fixing the altered bit
        alterBit(receivedCodedWord, controlSum);
        receivedInformationWord = decodeInformationWord(receivedCodedWord, codedLen, parityBit);

        std::cout << "Corrected information word: " << receivedInformationWord << "\n";
        std::cout << "Corrected coded word: " << receivedCodedWord << "\n";
    }
}