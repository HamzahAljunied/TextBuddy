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
	Texter(string);
	~Texter();

	void commandTexter(string, string, string);

#ifdef TESTMODE
	int getTotalNumberOfLines(void){
		return _totalNumOfLines;
	}

	string compressLineTest(){
		Texter testClass("emptyTextFile");

		string actualOutput = testClass.compressTextLine("Test*STRING?!@");

		return actualOutput;
	}
#endif
	
private:
	int _totalNumOfLines;
	string _textFileInUse;

	const string errorDeleteLine = "Error: Line number is beyond the text document's parameter\n";
	const string errorOpeningFile = "Error opening file\n";
	const string contentCleared = "All content deleted from ";
	const string fileEmpty = " is empty\n";
	const string errorAddLine = "No information was passed when adding a line\n";
	const string fileSorted = "Text file is sorted alphabetically.\n";
	const string emptySearchResults = "No search results found.\n";
	const string searchResultsMessage = "Search results:\n";

	const string addCommand = "add";
	const string deleteCommand = "delete";
	const string displayCommand = "display";
	const string clearCommand = "clear";
	const string sortCommand = "sort";
	const string searchCommand = "search";

	void addLine(string);
	void displayFileContents();
	void deleteLine(int);
	void clearTextFile();
	void sortLinesAlphabetically();
	void searchLines(string);

	bool isInformationValid(string);
	string compressTextLine(string);
	bool is_number(const string&);
	bool isWithinNumLineRange(int);
	void displaySearchLineResults(vector<string>);
	void readIntoFile(vector<string>&);
	int numOfLinesInFile();
	vector<string> readFileIntoVec();

};

#endif // !TEXTER_H
