#include "include/game.h"


game *game1 = nullptr;

using namespace std;

int main(int argc, char* argv[]) {
	Vector2 SCREEN_SIZE;
	Vector2 MAP_SIZE;
	game1 = new game();
	game1->init();
	while (game1->running()) {
		game1->handleEvent();
		game1->update();
		game1->render();
	}
	game1->clean();
	return 0;
}