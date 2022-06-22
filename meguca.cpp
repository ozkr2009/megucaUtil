#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <windows.h>
#include <cstdio>
#include <cstring>

class FileOps{
	std::string fileName;
	std::string outputFileName;
	std::string fileNameNoExt;

public:
	FileOps(std::string fileName){
		this->fileNameNoExt = fileName;
		this->fileName = fileName + ".json";
		this->outputFileName = fileName + ".txt";
	}

	// Extracts the text from the JSON file and dumps it into a txt file
	int extractText(){
		std::string line;		   // Current line
		std::string currentString; // For checking labels
		bool inString = false;	   // Check if we are inside of a ""
		bool quote = false;		   // Check if the string uses a special char
		bool isTextHome = false;   // Set flag if current string is textHome

		std::ifstream jsonFile(this->fileName);

		if (jsonFile.is_open()){
			std::ofstream outFile(this->outputFileName);

			while (std::getline(jsonFile, line)){
				for (char x : line){
					if (!inString){
						if (currentString == "textHome"){
							currentString = "";
							isTextHome = true;
						}
						if (x != ' '){
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
					}
					else{ // inString is True
						if (x == '\\'){
							quote = true;
							outFile << x;
							continue;
						}
						if (x == '"' && quote == false){
							inString = false;
						}
						else{
							currentString = currentString + x;
							if (isTextHome){
								outFile << x;
							}

							quote = false;
						}
					}
				}
				if (isTextHome){
					outFile << std::endl;
				}
				currentString = "";
				isTextHome = false;
			}
			return 0;
		}
		return 1;
	}

	int insertText(){
		std::string txtLine;	// current line from txt file
		std::string ogJsonLine; // current line from original Json file

		

		// Open txt file and original Json file
		std::ifstream txtFile(this->outputFileName);
		std::ifstream ogJsonFile(this->fileName);

		if (txtFile.is_open()){
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

			while (std::getline(newJsonFile, jsonLine)){
				newOgJsonFile << jsonLine << std::endl;
			}

			newJsonFile.close();
			newOgJsonFile.close();

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




	bool lineTextHome(std::string ogJsonLine){
		std::string currentString;
		bool inString = false;
		bool quote = false;
		bool isTextHome = false;

		for (char x : ogJsonLine){
			if(!inString){
				if (currentString == "textHome"){
					currentString = "";
					isTextHome = true;
					return true;
				}
				if (x != ' '){
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
			}
			else{
				if (x == '\\'){
					quote = true;
				}
				if (x == '"' && quote == false){
					inString = false;
				}else{
					currentString = currentString + x;
					if (isTextHome){
						return true;
					}

					quote = false;
				}
			}
		}
		return false;
	}

};

void showMenu();

int main(){
	SetConsoleTitle("Meguca Util v0.5a");

	showMenu();
}

void showMenu(){
	std::string option;
	std::string fileName;

	std::cout << "Bienvenido Meguca Util v0.5a\n";

	while (option != "0"){
		std::cout << "Men\xA3 principal:\n";
		std::cout << "1) Extraer texto de archivo JSON\n";
		std::cout << "2) Insertar texto al archivo JSON\n";
		std::cout << "0) Salir\n";
		std::cout << "Comando: ";
		std::cin >> option;

		if (option == "1"){
			std::cout << "\nExtraer texto de JSON...\n\n";
			std::cout << "Ingresa el nombre del archivo JSON sin la extensi\xA2n: ";
			std::cin >> fileName;

			FileOps fileOps = FileOps(fileName);

			if (fileOps.extractText() == 0){
				std::cout << "\n\xADListo, tu archivo se llama " + fileName + ".txt!\n\n";
			}
			else{
				std::cout << "El archivo " + fileName + ".json no existe en la carpeta actual.\n\n";
			}
		}
		else if (option == "2"){
			std::cout << "\nInsertar texto a archivo JSON...\n\n";
			std::cout << "Ingresa el nombre del archivo txt sin la extensi\xA2n: ";
			std::cin >> fileName;

			FileOps fileOps = FileOps(fileName);

			if(fileOps.insertText() == 0){
				std::cout << "\n\xADListo, tu archivo se llama " + fileName + ".json!\n\n";
			}
			else{
				std::cout << "El archivo " + fileName + ".txt no existe en la carpeta actual.\n\n";
			}
		}
		else if (option == "0"){
			break;
		}
		else{
			std::cout << "\nOpci\xA2n inv\xA0lida, intenta de nuez.\n\n";
		}
	}
	std::cout << "Te vas por la sombrita :3\n";
	Sleep(2000);
}