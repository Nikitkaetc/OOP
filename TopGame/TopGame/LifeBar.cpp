#include "LifeBar.h"

lifeBar::lifeBar()
{
	image.loadFromFile("images/lifeBar.png");
	image.createMaskFromColor(Color(237, 28, 36));
	t.loadFromImage(image);
	s.setTexture(t);
	s.setTextureRect(IntRect(0, 0, 125, 24));

	imageAva.loadFromFile("images/IronMan.png");
	imageAva.createMaskFromColor(Color(186, 254, 202));
	avaText.loadFromImage(imageAva);
	avaSprite.setTexture(avaText);
	avaSprite.setTextureRect(IntRect(80, 520, 24, 24));


	bar.setFillColor(Color(0, 0, 0));
	max = 100;
}

void lifeBar::Update(int k)

{
	if (k>0)
		if (k<max)
			bar.setSize(Vector2f((max - k) * 100 / max, 12));
}

void lifeBar::Draw(RenderWindow &window)
{
	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize();

	s.setPosition(center.x - size.x / 2 + 10, center.y - size.y / 2 + 10);
	avaSprite.setPosition(center.x - size.x / 2 + 10, center.y - size.y / 2 + 10);
	bar.setPosition(center.x - size.x / 2 + 32, center.y - size.y / 2 + 21);

	window.draw(s);
	window.draw(avaSprite);
	window.draw(bar);
}