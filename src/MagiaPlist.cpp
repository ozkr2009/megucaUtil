#include "MagiaPlist.h"

// Constructor 1
MagiaPlist::MagiaPlist(std::string fileNameNoExt){
	bool inFrames = false;
	bool inPNG = false;
	lines = 0;

	this->fileNameNoExt = fileNameNoExt;
	this->fileName = fileNameNoExt + ".plist";
	this->outputFile = fileNameNoExt + ".txt";
}

int MagiaPlist::extractData(){
	std::string line;		// Contains a single line from the plist file
	bool inTag = false;		// Inside a tag <...>
	std::string currentTag;	// Keeps name of the current tag
	std::string tagContent; 
	bool stop = false;

	std::ifstream plistFile(fileName);

	if(!plistFile.is_open())
		return 1;				// File does not exist

	std::ofstream framesFile(outputFile);

	// skip the first two lines of the file
	std::getline(plistFile, line);
	std::getline(plistFile, line);

	while(std::getline(plistFile, line)){
		for(char x:line){
			if(x == '<'){
				if(currentTag.compare("key") == 0){

					if(tagContent.find(".png") != std::string::npos){
						framesFile << tagContent << " ";
					}

					
				}else if(currentTag.compare("integer") == 0){
					framesFile << tagContent << " ";
				}else if(currentTag.compare("/dict") == 0){
					framesFile << "\n";
					lines++;
				}

				inTag = true;
				currentTag = "";
				continue;
			}else if(x == '>'){
				if(tagContent.compare("metadata") == 0){
					stop = true;
					break;
				}
				inTag = false;
				tagContent = "";
				continue;
			}

			if(inTag){
				currentTag = currentTag + x;
			}else if(currentTag.compare("key") == 0  || currentTag.compare("integer") == 0){
				if(x != '\t' && x != '\n'){
					tagContent += x;
				}
			}
		}

		if(stop)
			break;
	}

	plistFile.close();
	framesFile.close();

	lines = lines - 1;

	gatherData();
	
	return 0;
}

// Gathers data and puts in array of Sprite
void MagiaPlist::gatherData(){
	sprites = new Sprite[lines];
	std::string line;
	std::ifstream textFile(outputFile);
	int spaceCounter;
	std::string current;
	
	std::string fullFileName;
	int width; 
	int height; 
	int originalWidth;
	int originalHeight;
	int x; 
	int y;

	for(unsigned int i = 0; i < lines; i++){
		std::getline(textFile, line);
		spaceCounter = 0;

		for(char x:line){
			if(x != ' '){
				current = current + x;
			}else{
				spaceCounter++;
				if(spaceCounter == 1){
					fullFileName = fileNameNoExt + "_" +current;
					sprites[i].fileName = new char[fullFileName.length()+1];
					std::strcpy(sprites[i].fileName, fullFileName.c_str());
				}else if(spaceCounter == 2){
					sprites[i].width = std::stoi(current);
				}else if(spaceCounter == 3){
					sprites[i].height = std::stoi(current);
				}else if(spaceCounter == 4){
					sprites[i].originalWidth = std::stoi(current);
				}else if(spaceCounter == 5){
					sprites[i].originalHeight = std::stoi(current);
				}else if(spaceCounter == 6){
					sprites[i].x = std::stoi(current);
				}else if(spaceCounter == 7){
					sprites[i].y = std::stoi(current);
					break;
				}

				current = "";
			}
		}
	}

	/*
	for(unsigned int i = 0; i < lines; i++){
		std::cout << "File name: " << sprites[i].fileName << "Width: " <<  sprites[i].width << "Height: " << sprites[i].height << "X: " << sprites[i].x << "Y: " << sprites[i].y << std::endl;
	}*/

}

// Getters

void MagiaPlist::getData(Sprite sprites[]){
	for(unsigned int i = 0; i < lines; i++){
		sprites[i].fileName = this->sprites[i].fileName;
		sprites[i].width = this->sprites[i].width;
		sprites[i].height = this->sprites[i].height;
		sprites[i].originalWidth = this->sprites[i].originalWidth;
		sprites[i].originalHeight = this->sprites[i].originalHeight;
		sprites[i].x = this->sprites[i].x;
		sprites[i].y = this->sprites[i].y;
	}
}

unsigned int MagiaPlist::getNumLines(){
	return lines;
}

const char* MagiaPlist::getFileNameCString(){
	fileNameNoExtCString = new char [fileNameNoExt.length()+1];
	std::strcpy(fileNameNoExtCString, fileNameNoExt.c_str());
	return fileNameNoExtCString;
}

const char* MagiaPlist::getFileNameCStringPNG(){
	std::string fileNamePNG = fileNameNoExt + ".png";
	fileNamePNGCString = new char [fileNamePNG.length()+1];
	std::strcpy(fileNamePNGCString, fileNamePNG.c_str());
	return fileNamePNGCString;
}