#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>

using namespace sf;

extern void Menu(RenderWindow & window, Music& music_menu);

extern void MenuGameOver(RenderWindow & window, Music& music_menu);

void Draw(RenderWindow & window, Sprite & menuBg, Sprite & menu1, Sprite & menu2);

void IsMenu(RenderWindow & window, Sprite & menuBg, Sprite & menu1, Sprite & menu2);