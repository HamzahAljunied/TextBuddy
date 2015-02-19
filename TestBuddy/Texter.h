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

	vector<string> getFileVec(string textFile){
		Texter testClass(textFile);
		vector<string> testSortedVec;

		testClass.sortLinesAlphabetically();
		testSortedVec = testClass.readFileIntoVec();

		return testSortedVec;
	}

#endif
	
private:
	int _totalNumOfLines;
	string _textFileInUse;

	const string ERROR_DELETE_LINE_MSG = "Error: Line number is beyond the text document's parameter\n";
	const string ERROR_OPENING_FILE_MSG = "Error opening file\n";
	const string CONTENT_CLEARED_MSG = "All content deleted from ";
	const string FILE_EMPTY_MSG = " is empty\n";
	const string ERROR_ADD_LINE_MSG = "No information was passed when adding a line\n";
	const string FILE_SORTED_MSG = "Text file is sorted alphabetically.\n";
	const string EMPTY_SEARCH_RESULTS_MSG = "No search results found.\n";
	const string SEARCH_RESULTS_MSG = "Search results:\n";

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
