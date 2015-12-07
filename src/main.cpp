#include <SFML/Window.hpp>
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include "utils.h"
#include "renderwindow.h"
#include <chrono>
#include <SOIL/SOIL.h>

#define GLSL(src) "#version 150 \n" #src


int main()
{
  RenderWindow rw(800, 600, "David OpenGL textures");


  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  GLuint vbo;
  glGenBuffers(1, &vbo);

  GLfloat vertices[] = {

      -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
       0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
       0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
      -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
  };

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  //Vertex shader
  const char* vertexSrc = GLSL
  (
      in vec2 position;
      in vec3 color;
      in vec2 texcoord;
      out vec3 Color;
      out vec2 Texcoord;

      void main()
      {
          Color = color;
          Texcoord = texcoord;
          gl_Position = vec4(position, 0.0, 1.0);
      }
  );

  //Compile vertex shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSrc, NULL);
  glCompileShader(vertexShader);

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &_STATUS);
  CheckForErrors(vertexShader, "Error compiling vertex shader");

  //Compile fragment shader
  const char* fragmentSource = GLSL
  (

      in vec3 Color;
      in vec2 Texcoord;

      out vec4 outColor;
      uniform sampler2D tex;

      void main()
      {
        if(Texcoord.y < 0.5)
          outColor = texture(tex, Texcoord);
        else
          outColor = texture(tex, vec2(Texcoord.x, 1.0 - Texcoord.y));
      }

  );

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);
  CheckForErrors(fragmentShader, "Error compiling fragment shader");

  // Create an element array
      GLuint ebo;
      glGenBuffers(1, &ebo);

      GLuint elements[] = {
          0, 1, 2,
          2, 3, 0
      };
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

  //Link vertex and fragment shader
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glBindFragDataLocation(shaderProgram, 0, "outColor");
  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);

  //Layout vertex data
  GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
  GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
  GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);
  glEnableVertexAttribArray(colAttrib);
  glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
  glEnableVertexAttribArray(texAttrib);
  glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));

  //Texture
  GLuint tex;
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);

  //Load image
  int x, y;
  unsigned char* image = SOIL_load_image("/mnt/21B5C75E400717EA/downloads/ILTQq.png", &x, &y, 0, SOIL_LOAD_RGB);
  cout << "Image size: " << x << "X" << y << std::endl;
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  SOIL_free_image_data(image);

  //CLAMPING (wrapping)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  //FILTERING
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  //better way:
  glGenerateMipmap(GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

  while(rw.IsRunning())
    {
      // Clear the screen to black
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // Draw a rectangle from the 2 triangles using 6 indices
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            //swap buffers
            rw.GetWindow()->display();
    }

  //Clean
  //Cleanup
  glDeleteTextures(1, &tex);

  glDeleteProgram(shaderProgram);
  glDeleteShader(fragmentShader);
  glDeleteShader(vertexShader);

  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ebo);

  glDeleteVertexArrays(1, &vao);

  return 0;
}

int ex1()
{
    auto t_start = std::chrono::high_resolution_clock::now(); //uniform

    RenderWindow rw(800, 600, "David OpenGL");

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);


    GLfloat vert[] =
    {
      -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
      0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
      0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
      -0.5f, -0.5f, 1.0f, 1.0f, 1.0f  // Bottom-left
    };
// Normal triangle
//    GLfloat vert[] =
//    {
//      -0.5, 0.5f,
//      0.5f, 0.5f,
//      0.0f, -0.5f
//    };

    //Elements
    GLuint elements[] =
    {
      0, 1, 2,
      2, 3, 0
    };
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);


    //Vertex shader
    const char* vertexSrc = GLSL
    (
        in vec2 position;
        in vec3 color;
        out vec3 Color;

        void main()
        {
            Color = color;
            gl_Position = vec4(position, 0.0, 1.0);
        }
    );

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSrc, NULL);
    glCompileShader(vertexShader);


    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &_STATUS);
    CheckForErrors(vertexShader, "Error compiling vertex shader");

    //Fragment shader
    const char* fragmentSource = GLSL
    (

        uniform vec3 triangleColor;
        in vec3 Color;
        out vec4 outColor;

        void main()
        {
            outColor = vec4(triangleColor, 1.0);
            //outColor = vec4(Color, 1.0);
        }

    );

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    CheckForErrors(fragmentShader, "Error compiling fragment shader");


    //Link vertex and fragment shader
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    //Layout vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    //glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

    //Uniform
    GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");
    glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));


    //Render
    while(rw.IsRunning())
    {


        //Color transform
       auto t_now = std::chrono::high_resolution_clock::now();
       float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();


       // Clear the screen to black
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);


      //glDrawArrays(GL_TRIANGLES, 0, 3);
      glUniform3f(uniColor, (sin(time * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f);
      glDrawElements(GL_TRIANGLE_STRIP, 3, GL_UNSIGNED_INT, ((GLvoid *) 0));

      glUniform3f(uniColor, (cos(time * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f);
      glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, ((GLvoid *) 6)); //3*2


        //swap buffers
        rw.GetWindow()->display();
    }

    //Cleanup
    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
	return 0;
}
