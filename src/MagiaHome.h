#include <string>
#include <fstream>

class MagiaHome{
	std::string fileName;
	std::string outputFileName;
	std::string fileNameNoExt;


	public:
		// Constructor
		MagiaHome(std::string);

		// Extracts the text from the JSON file and dumps it into a txt file
		int extractText();

		// Inserts text back into the JSON file
		int insertText();

	private:
		// Checks if line contains a "textHome"
		bool lineTextHome(std::string);
};