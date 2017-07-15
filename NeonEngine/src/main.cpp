#include "app/window.h"

using namespace neon;

const GLint WIDTH = 800,
			HEIGHT = 600;

int main(void) {
	Window *window = new Window(WIDTH, HEIGHT, false, "Neon Engine");

	return EXIT_SUCCESS;
}