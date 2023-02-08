#include "include/game.h"
#include "include/mainMenu.h"



mainMenu* mm1 = nullptr;

using namespace std;

/*int main(int argc, char* argv[]) {
	game1 = new game();
	game1->init();
	while (game1->running()) {
		game1->handleEvent();
		game1->update();
		game1->render();
	}
	game1->clean();
	return 0;
}*/

Vector2 SCREEN_SIZE;
Vector2 MAP_SIZE;

int main(int argc, char* argv[]) {
	mm1 = new mainMenu();
	mm1->init();
	while (mm1->running()) {
		mm1->handleEvent();
		mm1->update();
		mm1->render();
	}
	mm1->clean();
	return 0;
}