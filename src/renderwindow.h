#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H
#include <GL/gl.h>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>
#include <functional>

class RenderWindow
{
public:
  RenderWindow(unsigned int sizeX, unsigned int sizeY, std::string title);
  ~RenderWindow();

  sf::Window* GetWindow();
  bool IsRunning();



private:
  sf::ContextSettings *_settingsPtr;
  sf::Window *_windowPtr;  
};

#endif // RENDERWINDOW_H
