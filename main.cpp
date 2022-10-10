#include "SFML/Graphics.hpp"
#include <iostream>
#include <stdio.h>
#include "Game.h"
#include "Vec2.h"

int main() {

	Game g("config.txt");
	g.run();
}