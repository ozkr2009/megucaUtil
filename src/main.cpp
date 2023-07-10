#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdio>
#include <cstring>
#include "MagiaHome.h"
#include "Ui.h"

int main(){
	Ui ui;

	
	ui.showWelcome();

	while(!ui.exitFlag()){
		ui.getMainMenuOption();

		if(ui.exitFlag())
			break;

		if(ui.getMainMenuOptionNum() == 1 || ui.getMainMenuOptionNum() == 2){
			MagiaHome magiaHome(ui.getFileNameNoExt());

			switch(ui.getMainMenuOptionNum()){
				case 1:
					if (magiaHome.extractText() == 0){
						std::cout << "\n\xADListo, tu archivo se llama " + ui.getFileNameNoExt() + ".txt!\n\n";
					}
					else{
						std::cout << "El archivo " + ui.getFileNameNoExt() + ".json no existe en la carpeta actual.\n\n";
					}
					break;
				case 2:
					
					if(magiaHome.insertText() == 0){
						std::cout << "\n\xADListo, tu archivo se llama " + ui.getFileNameNoExt() + ".json!\n\n";
					}
					else{
						std::cout << "El archivo " + ui.getFileNameNoExt() + ".txt no existe en la carpeta actual.\n\n";
					}
					break;
			}

			delete(&magiaHome);
		}

		
	}

	return 0;
}
