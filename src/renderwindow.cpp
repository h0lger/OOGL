#include "renderwindow.h"

RenderWindow::RenderWindow(unsigned int sizeX, unsigned int sizeY, std::string title)
{
    _settingsPtr = new sf::ContextSettings();
    _settingsPtr->depthBits = 24;
    _settingsPtr->stencilBits = 8;
    _settingsPtr->antialiasingLevel = 2;

    _windowPtr = new sf::Window(sf::VideoMode(sizeX, sizeY), title, sf::Style::Close, *_settingsPtr);


}

RenderWindow::~RenderWindow()
{

  std::cout << "~RenderWindow()" << std::endl;
  delete _windowPtr;
  delete _settingsPtr;
}

sf::Window* RenderWindow::GetWindow()
{
  return _windowPtr;
}

bool RenderWindow::IsRunning()
{
  sf::Event windowEvent;
  while(_windowPtr->pollEvent(windowEvent))
  {
      switch (windowEvent.type)
      {
        case sf::Event::Closed:
          std::cout << "Closed" << std::endl;
            return false;
        case sf::Event::KeyPressed:
          if(windowEvent.key.code == sf::Keyboard::Escape)
            {
              std::cout << "Escape" << std::endl;
              return false;
            }
        default:
          break;
      }
  }

  return true;
}

