#include <cstdio>
#include <string.h>
#include <cstring>
#include <iostream>
#include <fstream>

struct Sprite{
		char * fileName;
		int width; 
		int height; 
		int originalWidth;
		int originalHeight;
		int x; 
		int y;
	};

class MagiaPlist{
	char* fileNameNoExtCString;
	char* fileNamePNGCString;
	Sprite* sprites;
	std::string fileName;
	std::string fileNameNoExt;
	std::string outputFile;

	unsigned int lines;

	bool inFrames;
	bool inPNG;

	// Gathers data in a array of Sprite
	void gatherData();

	public:
		// Constructor 1
		MagiaPlist(std::string fileNameNoExt);

		// Extract texture information from plist file
		// Might store as 
		// 	fileName width height originalWidth originalHeight x y
		// in a file
		int extractData();

		

		// Gets the data
		void getData(Sprite sprites[]);

		// Gets number of lines
		unsigned int getNumLines();

		//Getters
		const char* getFileNameCString();

		const char* getFileNameCStringPNG();


};