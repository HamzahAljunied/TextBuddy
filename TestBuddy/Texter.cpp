#include "Texter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

Texter::Texter(void){
	_totalNumOfLines = 0;
}

Texter::~Texter(void){
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

void Texter::commandTexter(string userCommand, string information, char* argv[]){
	
	information.erase(information.begin());


	if(userCommand == "add"){
		if (isInformationValid(information)){
			addLine(information, argv);
		}
		else{
			cout << errorAddLine;
		}
	}
	if(userCommand == "display"){
		displayFileContents(argv);
	}
	if (userCommand == "clear"){
		clearTextFile(argv);
	}

	if (userCommand == "delete"){
		if (is_number(information)){
			int lineNumber;
			istringstream(information) >> lineNumber;

			if ((lineNumber <= _totalNumOfLines) && (lineNumber > 0)){
				deleteLine(lineNumber, argv);
			}
			else{
				cout << errorDeleteLine;
			}
		}
		else{
			cout << errorDeleteLine;
		}
	}
}

void Texter::addLine(string newLine, char* argv[]){
	vector<string> tempV;
	string textFileLine;
	ifstream textFile (argv[1]);

	if(textFile.is_open()){
		while(getline(textFile, textFileLine)){
			tempV.push_back(textFileLine);
		}

		tempV.push_back(newLine);
		cout<<newLine<<" was added to "<<argv[1]<<endl;
		textFile.trunc;
		textFile.close();

		_totalNumOfLines++;
	}
	else{
		cout<<errorOpeningFile;
	}

	ofstream newTextFile;
	newTextFile.open(argv[1]);
	for(vector<string>::iterator iter=tempV.begin(); iter!=tempV.end(); iter++){
		newTextFile << *iter <<endl;
	}

	tempV.erase(tempV.begin(), tempV.end());

	textFile.close();
}

void Texter::displayFileContents(char* argv[]){

	if (_totalNumOfLines == 0){
		cout << argv[1] << fileEmpty;
	}
	else{
		string line;
		ifstream textFile(argv[1]);
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

void Texter::deleteLine(int deletingLineNumber, char* argv[]){
	string textFileLine;
	string deletingLine;
	int i = 1;
	vector<string> tempV;
	ifstream textFile (argv[1]);

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
	newTextFile.open(argv[1]);

	for (vector<string>::iterator iter = tempV.begin(); iter != tempV.end(); iter++){
		newTextFile << *iter << endl;
	}
	
	cout << "deleted from my " << argv[1] << ": " << deletingLine << endl;
	_totalNumOfLines--;

	tempV.erase(tempV.begin(), tempV.end());	

}

void Texter::clearTextFile(char* argv[]){
	ofstream textFile;
	textFile.open(argv[1], ofstream::out | ofstream::trunc);
	textFile.close();

	cout << contentCleared << argv[1] << endl;
}
