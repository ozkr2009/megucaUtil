compile:
	g++ -std=c++17 -c src/main.cpp -o build/main.o
	g++ -std=c++17 -c src/MagiaHome.cpp -o build/MagiaHome.o
	g++ -std=c++17 -c src/Ui.cpp -o build/Ui.o
	g++ -std=c++17 -c src/MagiaSprite.cpp -o build/MagiaSprite.o
	g++ -std=c++17 -c src/MagiaPlist.cpp -o build/MagiaPlist.o
	windres res/resources.rc -O coff -o build/my.res
	g++ -std=c++17 -g build/my.res build/main.o build/MagiaHome.o build/Ui.o build/MagiaPlist.o build/MagiaSprite.o -o MegucaUtilv1.1a.exe

noIcon:
	g++ -std=c++17 -c src/main.cpp -o build/main.o
	g++ -std=c++17 -c src/MagiaHome.cpp -o build/MagiaHome.o
	g++ -std=c++17 -c src/Ui.cpp -o build/Ui.o
	g++ -std=c++17 -c src/MagiaSprite.cpp -o build/MagiaSprite.o
	g++ -std=c++17 -c src/MagiaPlist.cpp -o build/MagiaPlist.o
	g++ -std=c++17 -g build/main.o build/MagiaHome.o build/Ui.o build/MagiaPlist.o build/MagiaSprite.o -o MegucaUtilv1.1a.exe