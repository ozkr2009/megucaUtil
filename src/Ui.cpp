#include "Ui.h"

//
Ui::Ui(){
	exit = false;
}

//
void Ui::showWelcome(){
	std::cout << "Bienvenid@ a Meguca Util v1.1a\n";
}

void Ui::showBye(){
	std::cout << "Te vas por la sombrita :3\n";
	Sleep(1500);
}

//
void Ui::showMainMenu(){
	std::cout << "Men\xA3 principal:\n";
	std::cout << "1) Extraer texto de archivo JSON\n";
	std::cout << "2) Insertar texto al archivo JSON\n";
	std::cout << "3) Extraer im\xA0genes del sprite sheet\n";
	std::cout << "4) Insertar im\xA0genes al sprite sheet\n";
	std::cout << "0) Salir\n";
	std::cout << "Comando: ";
}

//
int Ui::getMainMenuOption(){
	bool valid = false;

	showMainMenu();

	while(true){
		std::cin >> option;

		if(option == "1"){
			this->optionNum = 1;
			showSubmenu1();
			return 1;
		}else if(option == "2"){
			this->optionNum = 2;
			showSubmenu1();
			return 2;
		}else if(option == "3"){
			this->optionNum = 3;
			showSubmenu1();
			return 3;
		}else if(option == "4"){
			this->optionNum = 4;
			showSubmenu1();
			return 4;
		}else if(option == "0"){
			this->optionNum = 0;
			this->exit = true;
			showBye();
			return 0;
		}

		std::cout << "\nOpci\xA2n inv\xA0lida, intenta de nuez.\n\n";
		showMainMenu();
	}

	
}



// Submenus

//
void Ui::showSubmenu1(){
	if(this->optionNum == 1)
		std::cout << "\nExtraer texto del archivo JSON...\n\n";
	else if(this->optionNum == 2)
		std::cout << "\nInsertar texto al archivo JSON...\n\n";
	else if(this->optionNum == 3)
		std::cout << "\nExtraer im\xA0genes del sprite sheet...\n\n";
	else if(this->optionNum == 4)
		std::cout << "\nInsertar im\xA0genes al sprite sheet...\n\n";

	this->fileName = getFileName();
}

//
std::string Ui::getFileName(){
	std::string fileName;
	std::string fileNameExt;
	bool fileExists = false;
	while(!fileExists){
		if (optionNum == 1 || optionNum == 2)
			std::cout << "Ingresa el nombre del archivo JSON sin la extensi\xA2n (\"x\" para cancelar): ";
		else if (optionNum == 3 || optionNum == 4)
			std::cout << "Ingresa el nombre del archivo PLIST sin la extensi\xA2n (\"x\" para cancelar): ";

		std::cin >> fileName;

		if(fileName == "x"){
			return fileName;
		}

		std::ifstream file;
		if(this->optionNum == 1){
			fileNameExt = fileName + ".json";
		}else if(this->optionNum == 2){
			fileNameExt = fileName + ".txt";
		}else if(this->optionNum == 3){
			fileNameExt = fileName + ".plist";
		}else if(this->optionNum == 4){
			fileNameExt = fileName + ".plist";
		}

		file.open(fileNameExt);

		if(file.is_open()){
			file.close();
			return fileName;
		}

		if(this->optionNum == 1){
			std::cout << "El archivo " + fileName + ".json no existe en la carpeta actual. Intenta de nuez.\n\n";
		}else if(this->optionNum == 2){
			std::cout << "El archivo " + fileName + ".txt no existe en la carpeta actual. Intenta de nuez.\n\n";
		}

	}

}

//

void Ui::start(){
	showWelcome();
	getMainMenuOption();
}

//
bool Ui::exitFlag(){
	return exit;
}

// 
int Ui::getMainMenuOptionNum(){
	return this->optionNum;
}

//
std::string Ui::getFileNameNoExt(){
	return this->fileName;
}