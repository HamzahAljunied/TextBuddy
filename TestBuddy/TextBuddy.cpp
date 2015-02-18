//Hamzah Aljunied, A0110783L
//CE2 Start

#include <iostream>
#include <fstream>
#include <string>
#include "Texter.h"

using namespace std;

void writeOnFile(char*[]);
bool isActionCommand(string userCommand);

const int REQ_NUM_OF_FILES = 2;
const string INVALID_COMMAND_INPUT = "Error: Incorrect command\n";
const string EXIT_PROGRAM = "TextBuddy exited\n";

int main(int argc, char* argv[]){

	if(argc < REQ_NUM_OF_FILES){
		cout<<"Error: Unable to start TextBuddy\n";
	}
	else{
		writeOnFile(argv);
	}

	return 0;
}

void writeOnFile(char* argv[]){
	string userCommand = "empty";
	string info= "empty";
	string textFileInUse = argv[1];
	Texter startTexter(textFileInUse);
	
	cout<<"Welcome to TextBuddy. "<<textFileInUse<<" is ready for use\n";

	cout << "command: ";
	while(cin>>userCommand){
		cout << endl;

		if (userCommand != "empty"){

			if (isActionCommand(userCommand)){
				getline(cin, info);
			}

			if ((userCommand != "exit")){
				startTexter.commandTexter(userCommand, info, textFileInUse);
			}
			else{
				break;
			}
		}
		else{
			cout << INVALID_COMMAND_INPUT;
		}

		userCommand = "empty";
		cout << "command: ";
	}

	cout << EXIT_PROGRAM;

	return;
}

bool isActionCommand(string userCommand){
	bool isAction = false;

	if ((userCommand == "add") || (userCommand == "delete") || (userCommand == "search")){
		isAction = true;
	}

	return isAction;
}
