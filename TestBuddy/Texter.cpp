#include "Texter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

Texter::Texter(string textFile){
	_textFileInUse = textFile;
	_totalNumOfLines = numOfLinesInFile(); //deduce the number of lines in the file used

}

int Texter::numOfLinesInFile(){
	string textFileLine;
	vector<string> textFileVec;
	ifstream readTextFile(_textFileInUse);
	int numOfLines = 0;

	if (readTextFile.is_open()){
		while (getline(readTextFile, textFileLine)){
			textFileVec.push_back(textFileLine);
			numOfLines++;
		}

		readTextFile.close();
	}

	textFileVec.erase(textFileVec.begin(), textFileVec.end());

	return numOfLines;
}

Texter::~Texter(){
	cout<<"Texter deleted\n";
}

//check if there is any information when the userCommand is passed
bool Texter::isInformationValid(string information){
	bool isValid = false;

	if (information != "empty" && information != "\n" && information != "" && information != " "){
		isValid = true;
	}
	
	return isValid;
}

bool Texter::isNumber(const string& s){

	bool isNum = false;

	string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)){
		++it;
	}

	if (!s.empty() && it == s.end()){
		isNum = true;
	}

	return isNum;
}

void Texter::commandTexter(string userCommand, string information, string fileInUse){
	
	information.erase(information.begin());

	if(userCommand == addCommand){
		if (isInformationValid(information)){
			addLine(information);
		}
		else{
			cout << ERROR_ADD_LINE_MSG;
		}
	}

	if(userCommand == displayCommand){
		displayFileContents();
	}

	if (userCommand == clearCommand){
		clearTextFile();
	}

	if (userCommand == deleteCommand){
		if (isNumber(information)){
			int lineNumber;
			istringstream(information) >> lineNumber;

			if (isWithinNumLineRange(lineNumber)){
				deleteLine(lineNumber);
			}
			else{
				cout << ERROR_DELETE_LINE_MSG;
			}
		}
		else{
			cout << ERROR_DELETE_LINE_MSG;
		}
	}

	if (userCommand == sortCommand){
		sortLinesAlphabetically();
	}

	if (userCommand == searchCommand){
		displaySearchLineResults(information);
	}
}

bool Texter::isWithinNumLineRange(int deleteNumLine){
	bool isWithinRange = false;

	if ((deleteNumLine <= _totalNumOfLines) && (deleteNumLine > 0)){
		isWithinRange = true;
	}

	return isWithinRange;
}

void Texter::addLine(string newLine){
	vector<string> tempV;
	string textFileLine;
	ifstream textFile (_textFileInUse);

	tempV = readFileIntoVec();

	tempV.push_back(newLine);
	cout << newLine << " was added to " << _textFileInUse << endl;
	textFile.trunc;
	textFile.close();

	readIntoFile(tempV);
	tempV.erase(tempV.begin(), tempV.end());
}

void Texter::displayFileContents(){

	if (_totalNumOfLines == 0){
		cout << _textFileInUse << FILE_EMPTY_MSG;
	}
	else{
		ifstream textFile(_textFileInUse);
		vector<string> displayVec;

		displayVec = readFileIntoVec();
		
		for (int i = 0; i < _totalNumOfLines; i++){
			cout << i+1 << ": " << displayVec[i] << endl;
		}
	}
}

void Texter::deleteLine(int deletingLineNumber){
	string textFileLine;
	string deletingLine;
	int currentLineNum = 1;
	vector<string> tempV;
	ifstream textFile (_textFileInUse);

	if(textFile.is_open()){
		while (getline(textFile, textFileLine)){
			if (currentLineNum != deletingLineNumber){
				tempV.push_back(textFileLine);
			}
			else{
				deletingLine = textFileLine;
			}

			currentLineNum++;
		}

		textFile.close();
	}
	else{
		cout<< ERROR_OPENING_FILE_MSG;
	}

	readIntoFile(tempV);
	tempV.erase(tempV.begin(), tempV.end());
	
	cout << "deleted from my " << _textFileInUse << ": " << deletingLine << endl;
	_totalNumOfLines--;	
}

//clear the text file of all contents
void Texter::clearTextFile(){
	ofstream textFile;
	textFile.open(_textFileInUse, ofstream::out | ofstream::trunc);
	textFile.close();

	_totalNumOfLines = 0;

	cout << CONTENT_CLEARED_MSG << _textFileInUse << endl;
}

//lines are sorted whereby special characters are ignored and is sorted purely alphabetically
void Texter::sortLinesAlphabetically(void){
	ifstream textFile(_textFileInUse);

	string textFileLine;
	string compressedLine;

	vector<string> originalTextFileVec; //used to store the lines in the text file and would not be editted
	vector<string> compressedTextFileVec; //used to store the lines after compressing it from all special characters and bringing it all tolower case
	vector<string>compressedSortedLinesVec; //used to store the compressed strings from originalTextFileVec and sort it
	vector<string> sortedLinesVec;

	originalTextFileVec = readFileIntoVec();
	compressedTextFileVec = readCompressedFileIntoVec();

	//sort the compressed lines in alphabetical order
	compressedSortedLinesVec = compressedTextFileVec;
	stable_sort(compressedSortedLinesVec.begin(), compressedSortedLinesVec.end());

	for (int i = 0; i < compressedSortedLinesVec.size(); i++){
		for (int j = 0; j < compressedTextFileVec.size(); j++){
			if (compressedSortedLinesVec[i] == compressedTextFileVec[j]){
				sortedLinesVec.push_back(originalTextFileVec[j]);

				//removes the string that has already been pushed into the desired sorting vector
				compressedTextFileVec.erase(compressedTextFileVec.begin() + j); 
				originalTextFileVec.erase(originalTextFileVec.begin() + j);

				i++; //to move the compressSortedLinesVec counter forward since it is already deleted
				j = -1; //moves j to its starting position
			}
		}
	}
	
	//input contents from the sortedVec into the designated text file
	readIntoFile(sortedLinesVec);

	sortedLinesVec.erase(sortedLinesVec.begin(), sortedLinesVec.end());
	originalTextFileVec.erase(originalTextFileVec.begin(), originalTextFileVec.end());
	compressedTextFileVec.erase(compressedTextFileVec.begin(), compressedTextFileVec.end());
	compressedSortedLinesVec.erase(compressedSortedLinesVec.begin(), compressedSortedLinesVec.end());

	cout << FILE_SORTED_MSG;
}

//removes all special characters from the string and returns the compressed string
string Texter::compressTextLine(string textLine){

	for (unsigned int i = 0; i < textLine.size(); i++){
		if (!isalpha(textLine[i])){
			textLine.erase(i, 1);
			i--;
		}
		else{
			if (isupper(textLine[i])){
				textLine[i] = tolower(textLine[i]);
			}
		}
	}

	return textLine; //returns textLine after being compressed
}

//puts the contents from the vector into the file specified
void Texter::readIntoFile(vector<string>& textFileContents){
	ofstream newTextFile;
	newTextFile.open(_textFileInUse);

	for (vector<string>::iterator iter = textFileContents.begin(); iter != textFileContents.end(); iter++){
		newTextFile << *iter << endl;
	}

	newTextFile.close();
}

vector<string> Texter::searchLines(string searchWord){

	vector<string> textLineVec;
	vector<string> searchResultVec;
	size_t found;

	textLineVec = readFileIntoVec();

	//searches for any instance of the search word within the file and stores it into searchResultVec
	for (unsigned int i = 0; i < textLineVec.size(); i++){
		found = textLineVec[i].find(searchWord);
		if (found != string::npos){
			searchResultVec.push_back(textLineVec[i]);
		}
	}

	return searchResultVec;
}

void Texter::displaySearchLineResults(string searchWord){
	
	vector<string> searchResults = searchLines(searchWord);

	if (searchResults.size() != 0){
		cout<<SEARCH_RESULTS_MSG;
		
		for (unsigned int i = 0; i < searchResults.size(); i++){
			cout << searchResults[i] << endl;
		}

		searchResults.erase(searchResults.begin(), searchResults.end());
	}
	else{
		cout << EMPTY_SEARCH_RESULTS_MSG;
	}

}

vector<string> Texter::readFileIntoVec(){
	ifstream textFile(_textFileInUse);
	string textFileLine;
	vector<string> textVec;

	if (textFile.is_open()){
		while (getline(textFile, textFileLine)){
			textVec.push_back(textFileLine);

			textFileLine.clear();
		}
	}
	else{
		cout << ERROR_OPENING_FILE_MSG;
	}

	return textVec;
}

vector<string> Texter::readCompressedFileIntoVec(){
	ifstream textFile(_textFileInUse);
	string compressedLine;
	vector<string> compressedTextVec;

	if (textFile.is_open()){
		while (getline(textFile, compressedLine)){
			compressedLine = compressTextLine(compressedLine);
			compressedTextVec.push_back(compressedLine);

			compressedLine.clear();
		}
	}
	else{
		cout << ERROR_OPENING_FILE_MSG;
	}

	return compressedTextVec;
}