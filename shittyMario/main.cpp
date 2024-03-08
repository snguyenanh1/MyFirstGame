#include <iostream>
#include "gameFunctions.h"
#include "graphic.h"
#include "menu.h"

int main(int argc, char* argv[]) {
	Menu menu;
	menu.loadMenu();
	menu.checkIfMousePressed();
	return 0;
}