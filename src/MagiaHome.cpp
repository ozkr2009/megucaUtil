#include "MagiaHome.h"

// Constructor
MagiaHome::MagiaHome(std::string fileName){
	this->fileNameNoExt = fileName;
	this->fileName = fileName + ".json";
	this->outputFileName = fileName + ".txt";
}


// Extracts the text from the JSON file and dumps it into a txt file
int MagiaHome::extractText(){
	std::string line;		   // Current line
	std::string currentString; // For checking labels
	bool inString = false;	   // Check if we are inside of a ""
	bool quote = false;		   // Check if the string uses a special char
	bool isTextHome = false;   // Set flag if current string is textHome

	std::ifstream jsonFile(this->fileName);		// Open JSON file

	if(jsonFile.is_open()){
		std::ofstream outFile(this->outputFileName);	// Open file to dump text
		
		while(std::getline(jsonFile, line)){
			for(char x: line){
				if(!inString){
					if(currentString == "textHome"){
						currentString = "";
						isTextHome = true;
					}
					if(x != ' '){
						switch(x){
							case '{':
								break;
							case '}':
								break;
							case '"':
								inString = true;
								break;
						}
					}
				}else{			// inString is true
					if(x == '\\'){
						quote = true;
						outFile << x;
						continue;
					}
					if(x == '"' && quote == false){
						inString = false;
					}else{
						currentString = currentString + x;
						if(isTextHome){
							outFile << x;
						}

						quote = false;
					}
				}
			}

			if(isTextHome){
				outFile << std::endl;
			}

			currentString = "";
			isTextHome = false;
		}

		return 0;
	}

	return 1;		// Something went wrong while opening the input file;
}

int MagiaHome::insertText(){
	std::string txtLine;	// current line from txt file
	std::string ogJsonLine; // current line from original Json file

	// Open txt file and original Json file
	std::ifstream txtFile(this->outputFileName);
	std::ifstream ogJsonFile(this->fileName);

	if(txtFile.is_open()){
		std::ofstream jsonFile(this->fileNameNoExt + ".test.json");

		getline(txtFile, txtLine);

		// parse original JSON file to find the "textHome" labels
		while (std::getline(ogJsonFile, ogJsonLine)){
			if(lineTextHome(ogJsonLine)){
				jsonFile << "\t\t\t\t\t\t\"textHome\": \"" + txtLine + "\"" << std::endl;
				getline(txtFile, txtLine);
			}else{
				jsonFile << ogJsonLine << std::endl;
			}
		}

		ogJsonFile.close();
		jsonFile.close();

		std::ofstream newOgJsonFile(this->fileName);
		std::ifstream newJsonFile(this->fileNameNoExt + ".test.json");
		std::string jsonLine;
		
		while(std::getline(newJsonFile, jsonLine)){
			newOgJsonFile << jsonLine << std::endl;
		}

		newJsonFile.close();
		newOgJsonFile.close();

		// Delete test file
		std::string fileDelName = this->fileNameNoExt + ".test.json";
		int fileDelNameLen = fileDelName.length();
		char fileDeleteName [fileDelNameLen + 1];
		for (int i = 0; i < fileDelNameLen; i++){
			fileDeleteName[i] = fileDelName[i];
		}
		fileDeleteName[fileDelNameLen] = '\0';

		std::remove(fileDeleteName);

		return 0;
	}

	return 1;
}

bool MagiaHome::lineTextHome(std::string ogJsonLine){
	std::string currentString;
	bool inString = false;
	bool quote = false;
	bool isTextHome = false;

	for(char x: ogJsonLine){
		if(!inString){
			if(currentString == "textHome"){
				currentString = "";
				isTextHome = true;
				return true;
			}

			if(x != ' '){
				switch (x){
					case '{':
						break;
					case '}':
						break;
					case '"':
						inString = true;
						break;
				}
			}
		}else{
			if(x == '\\'){
				quote = true;
			}

			if(x == '"' && quote == false){
				inString = false;
			}else{
				currentString = currentString + x;
				if(isTextHome){
					return true;
				}

				quote = false;
			}
		}
	}
	
	return false;
}