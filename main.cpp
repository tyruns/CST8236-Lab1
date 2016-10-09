#include <SFML/Graphics.hpp>
#include "TransformNode.h"

int main(int argc, char* argv) 
{
  sf::RenderWindow window(sf::VideoMode(600, 600), "Tyle Runions SFML Lab 1");
  
  sf::CircleShape head(6.0f, 30);
  sf::RectangleShape neck(sf::Vector2<float>(3.0f, 10.0f));
  sf::RectangleShape bod(sf::Vector2<float>(5.0f, 50.0f));

  sf::RectangleShape lowerArmRectR(sf::Vector2<float>(15.0f, 5.0f));
  sf::RectangleShape upperArmRectR(sf::Vector2<float>(15.0f, 5.0f));

  sf::RectangleShape lowerArmRectL(sf::Vector2<float>(15.0f, 5.0f));
  sf::RectangleShape upperArmRectL(sf::Vector2<float>(15.0f, 5.0f));

  head.setFillColor(sf::Color::Magenta);
  neck.setFillColor(sf::Color::Green);
  bod.setFillColor(sf::Color::Yellow);
  lowerArmRectR.setFillColor(sf::Color::Blue);
  upperArmRectR.setFillColor(sf::Color::Red);
  lowerArmRectL.setFillColor(sf::Color::Blue);
  upperArmRectL.setFillColor(sf::Color::Red);

  bool keyHeld = false;

  bool growing = true;
  float scaleFactor = 1.001;

  float growthFactor = 1.001f;
  float shrinkFactor = 0.999f;

  bod.setOrigin((bod.getLocalBounds().width/2), 0.0f); //To set origin in the middle of the screen (found online)
  bod.setPosition(300, 300);
  bod.setScale(4, 4);

  sf::Vector2<float> bodPosition(300, 500);
  sf::Vector2<float> bodOrigin((bod.getLocalBounds().width *0.5), bod.getLocalBounds().height);

  sf::Vector2<float> armPositionR((bod.getLocalBounds().width / 1.1f), (bod.getLocalBounds().height / 7.5f));
  sf::Vector2<float> armOriginR(0.0f, 2.5f);

  sf::Vector2<float> armPositionL((bod.getLocalBounds().width / 10.0f), (bod.getLocalBounds().height / 7.5f));
  sf::Vector2<float> armOriginL(15.0, 2.5f);

  sf::Vector2<float> neckPosition(bod.getLocalBounds().width *0.5, (bod.getLocalBounds().height /15.0));
  sf::Vector2<float> neckOrigin((neck.getLocalBounds().width * 0.5), neck.getLocalBounds().height);

  bod.setOrigin(bodOrigin);
  bod.setPosition(bodPosition);
  bod.setScale(5, 5);

  upperArmRectR.setOrigin(armOriginR);
  lowerArmRectR.setOrigin(armOriginR);

  upperArmRectL.setOrigin(armOriginL);
  lowerArmRectL.setOrigin(armOriginL);

  neck.setOrigin(neckOrigin);
  head.setOrigin((0.0), neck.getLocalBounds().height / 5.0f);

  lowerArmRectR.setPosition(15.0f, 2.5f);
  upperArmRectR.setPosition(armPositionR);

  lowerArmRectL.setPosition(0.0f, 2.5f);
  upperArmRectL.setPosition(armPositionL);

  neck.setPosition(neckPosition);
  head.setPosition((head.getLocalBounds().width / -3.0f), -5.0);

  TransformNode bodTransf(&bod);
  TransformNode neckTransf(&neck);
  TransformNode headTransf(&head);
  TransformNode upperArmRTransf(&upperArmRectR);
  TransformNode lowerArmRTransf(&lowerArmRectR);
  TransformNode upperArmLTransf(&upperArmRectL);
  TransformNode lowerArmLTransf(&lowerArmRectL);

  neckTransf.AddChild(&headTransf);
  bodTransf.AddChild(&neckTransf);
  upperArmRTransf.AddChild(&lowerArmRTransf);
  upperArmLTransf.AddChild(&lowerArmLTransf);
  bodTransf.AddChild(&upperArmRTransf);
  bodTransf.AddChild(&upperArmLTransf);

  sf::Clock deltaTime;
  while (window.isOpen())
  {
    float elaspedTime = deltaTime.restart().asSeconds();

    sf::Transform transform = bod.getTransform();
    sf::Event sfEvent;
    while (window.pollEvent(sfEvent))
    {
      if (sfEvent.type == sf::Event::Closed)
      {
        window.close();
      }
    }

	float maxAngle = 30.0f;
	float minAngle = 330.0f; 
	float speed = 90.0f * elaspedTime;
	float bodyRotation = bod.getRotation();


	if (bodyRotation >= maxAngle && bodyRotation < minAngle) 
	{ growing = false; }

	if (bodyRotation <= minAngle && bodyRotation >= 180.0) 
	{ growing = true; }

	if (bodyRotation <= maxAngle && bodyRotation >= maxAngle) 
	{ growing = true; }

	if (growing)
	{
		lowerArmRectL.rotate(-speed);
		upperArmRectL.rotate(-speed);
		lowerArmRectR.rotate(speed);
		upperArmRectR.rotate(speed);
		bod.rotate(speed);
		neck.rotate(speed);
	}
	if (!growing)
	{
		lowerArmRectL.rotate(speed);
		upperArmRectL.rotate(speed);
		lowerArmRectR.rotate(-speed);
		upperArmRectR.rotate(-speed);
		bod.rotate(-speed);
		neck.rotate(-speed);
	}

    window.clear(); // draw fullscreen graphic

    bodTransf.Draw(&window);

    window.display();
  }

  return 0;
}