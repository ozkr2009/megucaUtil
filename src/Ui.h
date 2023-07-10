#include <iostream>
#include <string>
#include <windows.h>	// For Windows Sleep()
#include <unistd.h>		// For Linux Sleep()
#include <fstream>

class Ui{
	std::string option;
	int optionNum;
	std::string fileName;
	bool exit;

	public:
		// Constructor
		Ui();

		// Displays welcome message
		void showWelcome();

		// Displays main menu
		void showMainMenu();

		// Returns flag to exit
		bool exitFlag();

		// Gets main menu option
		int getMainMenuOption();

		// Returns main menu option number
		int getMainMenuOptionNum();

		// Returns fileName (no extension)
		std::string getFileNameNoExt();

	private:
		// Displays bye message
		void showBye();

		// Show "1" submenu
		void showSubmenu1();

		// Get fileName from user
		std::string getFileName();

		// Starts menu
		void start();

};