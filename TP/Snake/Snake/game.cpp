#include "game.h"
#include "map.h"





Game::Game(RenderWindow &window)
{
	time = 0;
	texture.loadFromFile("texture.png");
	fieldSprite.setTexture(texture);
	blockSprite.setTexture(texture);
	fieldSprite.setTextureRect(IntRect(0, 0, 32, 32));
	blockSprite.setTextureRect(IntRect(32, 0, 32, 32));
	font.loadFromFile("Font.ttf");
}

void Game::DoGameLoop(RenderWindow& window, GameMode & gameMode)
{
	parts = snake.ReturnParts();
	apple.SpawnNewApple(parts);
	Text text("", font, 30);
	text.setColor(Color::Green);
	while (window.isOpen())
	{
		window.clear();
		Event event;
		while (window.pollEvent(event))
			if (event.type == Event::Closed)
				window.close();

		switch (gameMode)
		{
		case GameMode::MENU:
			text.setString("Press Enter to play");
			text.setPosition(180, 220);
			window.draw(text);
			if (Keyboard::isKeyPressed(Keyboard::Return))
			{
				snake.ResetSnake();
				gameMode = GameMode::PLAY;
			}
			break;
		case GameMode::END:
			text.setString("GAME OVER");
			text.setPosition(230, 180);
			window.draw(text);
			current = snake.ReturnSize();
			if (score)
			{
				playerScoreString.str("");
				playerScoreString << (current - 1) * 10;
				score = false;
			}
			text.setString("SCORE: " + playerScoreString.str());
			text.setPosition(240, 250);
			window.draw(text);
			text.setString("Press Enter to restart");
			text.setPosition(160, 350);
			window.draw(text);
			if (Keyboard::isKeyPressed(Keyboard::Return))
			{
				snake.ResetSnake();
				gameMode = GameMode::PLAY;
			}

			break;
		case GameMode::PLAY:
			time = 0;
			while (time < TIME_STEP)
			{
				snake.ProcessEvents(window);
				time = clock.getElapsedTime().asMilliseconds();
			}

			if (time >= TIME_STEP)
			{
				clock.restart(); 

				snake.ProcessEvents(window);       
				snake.Tick();	
				snake.Update();                    

				parts = snake.ReturnParts();

				if (apple.CheckEventApple(parts))
				{
					snake.AddNewSnakePart();
				}
				if (snake.CheckGameOver())
				{
					gameMode = GameMode::END;
					score = true;
				}
				DrawMap(window, fieldSprite, blockSprite);
				snake.DrawSnake(window);
				apple.DrawApple(window);
			}
			break;
		}
		window.display();
	}
}