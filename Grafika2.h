// bbb.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <GL\glew.h>
#include <SFML\Window.hpp>
#include <iostream>


// Kody shaderów
const GLchar* vertexSource = R"glsl(
#version 150 core
in vec3 position;
in vec3 color;
out vec3 Color;
void main(){
Color = color;
gl_Position = vec4(position, 1.0);
}
)glsl";

const GLchar* fragmentSource = R"glsl(
#version 150 core
in vec3 Color;
out vec4 outColor;
void main()
{
outColor = vec4(Color, 1.0);
}
)glsl";

void display(int points, GLuint vbo) {
	GLfloat* vertices = new GLfloat[6 * points];

	float r = 1;
	float pi = 3.14;
	float alpha = 0;
	float delta_alpha = 2 * pi / points;
	float color = 1.0;
	for (int i = 0; i < 6 * points; i += 6) {
		vertices[i] = r * cos(alpha);
		vertices[i + 1] = r * sin(alpha);
		vertices[i + 2] = 1.0;
		vertices[i + 3] = color -= 0.005;
		vertices[i + 4] = color -= 0.005;
		vertices[i + 5] = color -= 0.005;

		alpha += delta_alpha;
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * points * 6, vertices, GL_STATIC_DRAW);
	delete[] vertices;
}

int main()
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;

	// Okno renderingu
	sf::Window window(sf::VideoMode(800, 600, 32), "OpenGL", sf::Style::Titlebar | sf::Style::Close, settings);

	// Inicjalizacja GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	// Utworzenie VAO (Vertex Array Object)
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Utworzenie VBO (Vertex Buffer Object)
	// i skopiowanie do niego danych wierzchołkowych
	GLuint vbo;
	glGenBuffers(1, &vbo);

	// ---------------------------------------------------
	display(10, vbo);

	// Utworzenie i skompilowanie shadera wierzchołków
	GLuint vertexShader =
		glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	// Utworzenie i skompilowanie shadera fragmentów
	GLuint fragmentShader =
		glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	// Zlinkowanie obu shaderów w jeden wspólny program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	// Specifikacja formatu danych wierzchołkowych
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	// -------------------------------------------------

	GLint isCompiled = 0;
	GLint maxLength = 255;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		std::vector<GLchar> errorLog1(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &errorLog1[0]);
		std::cout << "fragment shader: " << &errorLog1[0] << "\n";
		glDeleteShader(fragmentShader);
	}
	isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		std::vector<GLchar> errorLog2(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &errorLog2[0]);
		std::cout << "fragment shader " << &errorLog2[0] << "\n";
		glDeleteShader(vertexShader);
	}

	// ---------------------------------------------------

	// Rozpoczęcie pętli zdarzeń
	bool running = true;
	int type = GL_TRIANGLE_FAN;
	int points = 100;
	int previousPosition = 100;
	int actualPosition = 100;

	while (running) {
		sf::Event windowEvent;
		while (window.pollEvent(windowEvent)) {
			switch (windowEvent.type) {
			case sf::Event::Closed:
				running = false;
				break;
			}
		}

		// zmiana liczby wierzcholkow
		sf::Vector2i position = sf::Mouse::getPosition(window);
		if (position.y > 0 && position.y != actualPosition) {
			previousPosition = actualPosition;
			actualPosition = position.y;
			points = actualPosition;

			display(points, vbo);
		}

		// Nadanie scenie koloru czarnego
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Narysowanie trójkąta na podstawie 3 wierzchołków
		glDrawArrays(type, 0, points);
		// Wymiana buforów tylni/przedni
		window.display();

		// zmiana prymitywu
		switch (windowEvent.key.code) {
		case sf::Keyboard::Escape:
			running = false;
			break;
		case sf::Keyboard::Num0:
			type = GL_TRIANGLE_FAN;
			break;
		case sf::Keyboard::Num1:
			type = GL_POINTS;
			break;
		case sf::Keyboard::Num2:
			type = GL_LINES;
			break;
		case sf::Keyboard::Num3:
			type = GL_POLYGON;
			break;
		case sf::Keyboard::Num4:
			type = GL_LINE_STRIP;
			break;
		case sf::Keyboard::Num5:
			type = GL_TRIANGLES;
			break;
		case sf::Keyboard::Num6:
			type = GL_LINE_LOOP;
			break;
		case sf::Keyboard::Num7:
			type = GL_QUAD_STRIP;
			break;
		case sf::Keyboard::Num8:
			type = GL_TRIANGLE_STRIP_ADJACENCY;
			break;
		case sf::Keyboard::Num9:
			type = GL_LINES_ADJACENCY;
			break;
		}
	}
	// Kasowanie programu i czyszczenie buforów
	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	// Zamknięcie okna renderingu
	window.close();
	return 0;
}

