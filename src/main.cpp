#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdio>
#include <cstring>
#include "MagiaHome.h"
#include "Ui.h"
#include "MagiaPlist.h"
#include "MagiaSprite.h"


int main(){
	Ui ui;

	MagiaSprite *magiaSprite;
	
	ui.showWelcome();

	while(!ui.exitFlag()){
		ui.getMainMenuOption();

		if(ui.exitFlag())
			break;

		if(ui.getMainMenuOptionNum() == 1 || ui.getMainMenuOptionNum() == 2){
			if(ui.getFileNameNoExt() == "x")
				continue;

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

		}else if(ui.getMainMenuOptionNum() == 3 || ui.getMainMenuOptionNum() == 4){
			if(ui.getFileNameNoExt() == "x")
				continue;

			Sprite * sprites;
			MagiaPlist magiaPlist(ui.getFileNameNoExt());
			magiaSprite = new MagiaSprite(magiaPlist.getFileNameCStringPNG());
			magiaPlist.extractData();
			MagiaSprite* fragment;
			
			sprites = new Sprite[magiaPlist.getNumLines()];
			magiaPlist.getData(sprites);


			switch(ui.getMainMenuOptionNum()){
				case 3:
					std::cout << "Extrayendo...\n";
					for(unsigned int i = 0; i < magiaPlist.getNumLines(); i++){
						magiaSprite->extract(sprites[i].x, sprites[i].y, sprites[i].width, sprites[i].height, sprites[i].fileName);
						std::cout << sprites[i].fileName << std::endl;
					}
					std::cout << "Listo!\n\n";
					break;
				case 4:
					std::cout << "Insertando...\n";
					for(unsigned int i = 0; i < magiaPlist.getNumLines(); i++){
						delete(&magiaSprite);
						magiaSprite = new MagiaSprite(magiaPlist.getFileNameCStringPNG());
						fragment = new MagiaSprite(sprites[i].fileName); 
						magiaSprite->overlay(*fragment, sprites[i].x, sprites[i].y, magiaPlist.getFileNameCStringPNG());

						std::cout << sprites[i].fileName << std::endl;

						delete(fragment);
					}
					std::cout << "Listo!\n\n";
					break;			
			}

			
			delete(&sprites);
			delete(&magiaPlist);
			delete(&magiaSprite);
			
		}

		
	}

	return 0;
}