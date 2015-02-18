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
	_totalNumOfLines = 0;

	string textFileLine;
	vector<string> textFileVec;
	ifstream readTextFile(_textFileInUse);

	if (readTextFile.is_open()){
		while (getline(readTextFile, textFileLine)){
			textFileVec.push_back(textFileLine);
			_totalNumOfLines++;
		}

		readTextFile.close();
	}

	textFileVec.erase(textFileVec.begin(), textFileVec.end());
}

Texter::~Texter(){
	cout<<"Texter deleted\n";
}

bool Texter::isInformationValid(string information){
	bool isValid = false;

	if (information != "empty" && information != "\n" && information != "" && information != " "){
		isValid = true;
	}
	
	return isValid;
}

bool Texter::is_number(const string& s){

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
			cout << errorAddLine;
		}
	}

	if(userCommand == displayCommand){
		displayFileContents();
	}

	if (userCommand == clearCommand){
		clearTextFile();
	}

	if (userCommand == deleteCommand){
		if (is_number(information)){
			int lineNumber;
			istringstream(information) >> lineNumber;

			if (isWithinNumLineRange(lineNumber)){
				deleteLine(lineNumber);
			}
			else{
				cout << errorDeleteLine;
			}
		}
		else{
			cout << errorDeleteLine;
		}
	}

	if (userCommand == sortCommand){
		sortLinesAlphabetically();
	}

	if (userCommand == searchCommand){
		searchLines(information);
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

	if(textFile.is_open()){
		while(getline(textFile, textFileLine)){
			tempV.push_back(textFileLine);
		}

		tempV.push_back(newLine);
		cout<<newLine<<" was added to "<<_textFileInUse<<endl;
		textFile.trunc;
		textFile.close();

		_totalNumOfLines++;
	}
	else{
		cout<<errorOpeningFile;
	}

	ofstream newTextFile;
	newTextFile.open(_textFileInUse);
	for(vector<string>::iterator iter=tempV.begin(); iter!=tempV.end(); iter++){
		newTextFile << *iter <<endl;
	}

	tempV.erase(tempV.begin(), tempV.end());

	newTextFile.close();
}

void Texter::displayFileContents(){

	if (_totalNumOfLines == 0){
		cout << _textFileInUse << fileEmpty;
	}
	else{
		string line;
		ifstream textFile(_textFileInUse);
		int i = 1;

		if (textFile.is_open()){
			while (getline(textFile, line)){
				cout << i << ": " << line << endl;
				i++;
			}

			textFile.close();
		}
		else{
			cout << errorOpeningFile;
		}
	}
}

void Texter::deleteLine(int deletingLineNumber){
	string textFileLine;
	string deletingLine;
	int i = 1;
	vector<string> tempV;
	ifstream textFile (_textFileInUse);

	if(textFile.is_open()){
		while (getline(textFile, textFileLine)){
			if (i != deletingLineNumber){
				tempV.push_back(textFileLine);
			}
			else{
				deletingLine = textFileLine;
			}

			i++;
		}

		textFile.close();
	}
	else{
		cout<< errorOpeningFile;
	}

	
	ofstream newTextFile;
	newTextFile.open(_textFileInUse);

	for (vector<string>::iterator iter = tempV.begin(); iter != tempV.end(); iter++){
		newTextFile << *iter << endl;
	}
	
	cout << "deleted from my " << _textFileInUse << ": " << deletingLine << endl;
	_totalNumOfLines--;

	tempV.erase(tempV.begin(), tempV.end());	
	newTextFile.close();
}

//clear the text file of all contents
void Texter::clearTextFile(){
	ofstream textFile;
	textFile.open(_textFileInUse, ofstream::out | ofstream::trunc);
	textFile.close();

	_totalNumOfLines = 0;

	cout << contentCleared << _textFileInUse << endl;
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


	if (textFile.is_open()){
		while (getline(textFile, textFileLine)){
			originalTextFileVec.push_back(textFileLine);

			compressedLine = compressTextLine(textFileLine);
			compressedTextFileVec.push_back(compressedLine);

			textFileLine.clear();
			compressedLine.clear();
		}

		textFile.close();
	}


	//sort the compressed lines in alphabetical order
	compressedSortedLinesVec = compressedTextFileVec;
	stable_sort(compressedSortedLinesVec.begin(), compressedSortedLinesVec.end());

	for (unsigned int i = 0; i < compressedSortedLinesVec.size(); i++){
		for (unsigned int j = 0; j < compressedTextFileVec.size(); j++){
			if (compressedSortedLinesVec[i] == compressedTextFileVec[j]){
				sortedLinesVec.push_back(originalTextFileVec[j]);

				compressedTextFileVec.erase(compressedTextFileVec.begin() + j);
				originalTextFileVec.erase(originalTextFileVec.begin() + j);

				i++; //to move the compressLinesVec counter forward since it is already deleted
				j = -1;
			}
		}
	}
	
	ofstream newTextFile;
	newTextFile.open(_textFileInUse);

	for (vector<string>::iterator iter = sortedLinesVec.begin(); iter != sortedLinesVec.end(); iter++){
		newTextFile << *iter << endl;
	}

	cout << fileSorted;

	newTextFile.close();
	sortedLinesVec.erase(sortedLinesVec.begin(), sortedLinesVec.end());
}

vector<string> Texter::searchLines(string){

	vector<string> textFileLines;

	return textFileLines;
}

void Texter::displaySearchLineResults(vector<string>){

}

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

	return textLine; //textLine after being compressed
}