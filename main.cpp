/*
Title:			CSGO Lyrics Script Generator

Description:	Generates a cfg script based on a lyrics file that allows the player to
			 	display the lyrics of any song line by line, using only one key bind.
			 	
Author: 		ThioJoe 	www.youtube.com/user/ThioJoe
							www.youtube.com/user/CacheGaming
							
Comipling:		Compile with ISO C++11
*/

#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <array>
#include <limits>

using namespace std;

int main(int argc, char** argv) {
    SetConsoleTitle("CSGO Lyrics Bind Generator");
    ofstream myfile;
	
	//Initialize Variables
	const int max = 250; //set max number of lines
	std::array<string, max> line;
	int numOfLines = 0;
	int lineNum = 0;
	string key = "MOUSE3"; //Default key to be bound
	string nextline;
	string filename;
	
	//Instructions
	cout << "=====CSGO Lyrics Script by ThioJoe: YouTube.com/ThioJoe=====" << endl << endl;
	cout << "Generates a cfg script based on a lyrics file that allows the player "
		 <<	"to display the lyrics of any song line by line, using only one key bind." << endl << endl;
	cout << "INSTRUCTIONS:" << endl;
	cout << "1. Put lyrics into a file called lyrics.txt - Max 250 Lines" << endl;
	cout << "2. Remove all blank lines and quotation ( \" ) marks" << endl;
	cout << "3. Exec NameYouPicked.cfg in csgo console - it will be bound to MOUSE3" << endl;
	cout << "4. To change the bind key, simply edit the produced .cfg file" << endl << endl;
	cout << "What should the file be called? (Not including .cfg)" << endl;
	
	//Creates name for file in filename variable
	cin >> filename;
	filename = filename+".cfg";
	cout << "File will be called " << filename << endl << endl;
	
	
	//Loads whatever is in lyrics.txt into array line by line
	//Simultaneously counts number of lines in lyrics.txt
	std::ifstream lyrics ("lyrics.txt");
	for(int i = 1; lyrics.good(); i++)
	{
	    getline(lyrics, line[i-1]);
	    numOfLines++;
	}	
	cout << "Found " << numOfLines << " lines" << endl;
	
	//Creates new text file with given name
	//If it already exists, this erases it's contents
	myfile.open (filename);
	myfile << "";
	myfile.close();
	
	//Prints initial script info into file
	myfile.open (filename, fstream::out | fstream::app);
	myfile << "bind " + key + " \"next_line\"" << endl;
	myfile << "alias c0 \"alias next_line c1;\"" << endl;
	
	//Prints each iteration for however many lines were found
	for (int i=1; i<=numOfLines; i++)
    {	
    	string nextline = line[lineNum];
  		myfile << "alias c" << i << " \"say " << nextline << "; alias next_line c" << i+1 << ";\"" << endl;
		lineNum++;	
	}
	
	//Adds blank aliases to nullify any previously-loaded lyric scripts
	for (int i = numOfLines+1; i<=max; i++){
		myfile << "alias c" << i << " \"alias next_line c" << i+1 << ";\"" << endl;
	}
	//Prints c0 at end to be executed
	myfile << "c0;";
	
	//Close File
	myfile.close();
	
	//Write Success
	cout << "Finished." << endl << endl;
	cout << "Place your new file into the \"cfg\" folder in your CSGO directory." << endl;
	cout << "To use, open console in game and type \"exec YourFileName.cfg\"" << endl;
	cout << "Press MOUSE3 (Middle Mouse) repeatedly to display lines of text."  << endl << endl << endl;
	
	//Pause
	string pause;
	cout << "Done! You can now close the program." << endl;
	cin >> pause;
	
	return 0;
}
