#ifndef UTILS_H
#define UTILS_H
#include <SFML/Window.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <ios>
#include <GL/gl.h>

using namespace std;
//GLOBAL
GLint _STATUS;
string _WINDOW_TITLE = "My OpenGL";

sf::ContextSettings _settings;
sf::Window _window;

char* ReadFile(string &filename)
{
    std::ifstream fstream;
     fstream.open(filename.c_str(), ios_base::in);
     char* output = new char[100];

     if (fstream.is_open())
     {
        while (!fstream.eof())
        {

            fstream >> output;
        }
    }
    else
     {
        cerr << "Error loading file";
     }
    fstream.close();
    return output;
}

int CheckForErrors(GLuint shader, string errMsg)
{
  if(_STATUS != GL_TRUE)
    {
      cerr << errMsg << endl;
      char buffer[512];
      glGetShaderInfoLog(shader, 512, NULL, buffer);
      cout << buffer;
      return 1;
    }

}

std::vector<std::string> Split(const std::string &s, char delim)
{
    std::vector<std::string> elems;

    const char* cstr = s.c_str();
    unsigned int strLength = s.length();
    unsigned int start = 0;
    unsigned int end = 0;

    while(end <= strLength)
    {
        while(end <= strLength)
        {
            if(cstr[end] == delim)
                break;
            end++;
        }

        elems.push_back(s.substr(start, end - start));
        start = end + 1;
        end = start;
    }

    return elems;
}

//void InitWindow(unsigned int x, unsigned int y)
//{
//  _settings.depthBits = 24;
//  _settings.stencilBits = 8;
//  _settings.antialiasingLevel = 2;

//  _window(sf::VideoMode(800, 600), "test", sf::Style::Close, _settings);

//}

#endif
