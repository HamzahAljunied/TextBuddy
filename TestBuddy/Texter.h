#pragma once
#ifndef TEXTER_H
#define TEXTER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class Texter
{
public:
	Texter();
	~Texter();

	void commandTexter(string, string, char* []);

#ifdef TESTMODE
	int getTotalNumberOfLines(void){
		return _totalNumOfLines;
	}

#endif
	
private:
	int _totalNumOfLines;

	const string errorDeleteLine = "Error: Line number is beyond the text document's parameter\n";
	const string errorOpeningFile = "Error opening file\n";
	const string contentCleared = "All content deleted from ";
	const string fileEmpty = "is empty\n";
	const string errorAddLine = "No information was passed when adding a line\n";

	void addLine(string, char*[]);
	void displayFileContents(char*[]);
	void deleteLine(int, char*[]);
	void clearTextFile(char*[]);
	void sortTextLines(void);
	bool isInformationValid(string);
	bool is_number(const string&);
	vector<string> searchLines(string);
	void displaySearchLineResults(vector<string>);
};

#endif // !TEXTER_H
