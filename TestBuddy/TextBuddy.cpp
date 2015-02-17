//Hamzah Aljunied, A0110783L
//CE2 Start

#include <iostream>
#include <fstream>
#include <string>
#include "Texter.h"

using namespace std;

void writeOnFile(char*[]);
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
	Texter ax;
	string userCommand = "empty";
	string info= "empty";
	
	cout<<"Welcome to TextBuddy. "<<argv[1]<<" is ready for use\n";

	cout << "command: ";
	while(cin>>userCommand){
		cout << endl;

		if (userCommand != "empty"){

			if ((userCommand == "add") || (userCommand == "delete")){
				getline(cin, info);
			}

			if ((userCommand != "exit")){
				ax.commandTexter(userCommand, info, argv);
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
