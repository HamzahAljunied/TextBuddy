#include "Texter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

Texter::Texter(){
	_totalNumOfLines = 0;
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

bool Texter::is_number(const string& s)
{
	string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
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

	textFile.close();
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

}

//clear the text file of all contents
void Texter::clearTextFile(){
	ofstream textFile;
	textFile.open(_textFileInUse, ofstream::out | ofstream::trunc);
	textFile.close();

	cout << contentCleared << _textFileInUse << endl;
}

//lines are sorted whereby special characters are ignored and is sorted purely alphabetically
void Texter::sortLinesAlphabetically(void){
	ifstream textFile(_textFileInUse);

	SEARCH_STRUCT textFileLine;
	SEARCH_STRUCT compressedLine;

	vector<SEARCH_STRUCT> originalTextFileVec; //used to store the lines in the text file and would not be editted
	vector<SEARCH_STRUCT> edittedTextFileVec; //used to store the lines after compressing it from all special characters and bringing it all tolower case

	int numLine = 1;

	if (textFile.is_open()){
		while (getline(textFile, textFileLine.textLine)){
			textFileLine.lineNum = numLine;
			originalTextFileVec.push_back(textFileLine);

			compressedLine.textLine = compressTextLine(textFileLine.textLine);
			compressedLine.lineNum = numLine;
			edittedTextFileVec.push_back(compressedLine);
		}
	}
}

vector<string> Texter::searchLines(string){

	vector<string> textFileLines;

	return textFileLines;
}

void Texter::displaySearchLineResults(vector<string>){

}

string Texter::compressTextLine(string textLine){

	for (int i = 0; i < textLine.size(); i++){
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