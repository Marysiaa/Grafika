// gk3d1111.cpp : Defines the entry point for the console application.

#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include "freeglut.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <math.h>
#include <stdlib.h>
// #include "glut.h"
//#include <GL/glut.h>
#include <stdlib.h>

// stała do obsługi menu podręcznego
enum
{
	EXIT // wyjście
};

double PredkoscKamery = 0;

// pionowy kąt pola widzenia
GLdouble fovy = 60;
float czajnikrot = 0;

// wpółrzędne położenia obserwatora
GLdouble eyex = 0;
GLdouble eyey = 0;
GLdouble eyez = 3;
GLdouble ObrotX = 3.14 / 2.0;
GLdouble ObrotY = 0;
bool KeyUP = false;
bool KeyDOWN = false;
bool KeyRIGHT = false;
bool KeyLEFT = false;

// współrzędne punktu w którego kierunku jest zwrócony obserwator,
GLdouble centerx = 0;
GLdouble centery = 0;
GLdouble centerz = -100;
int figure = 0;
float kat = 0;
GLuint idlisty;

// funkcja generująca scenę 3D
void GenerujListyWyswietlania()
{
	idlisty = glGenLists(4);
	// utworzenie pierwszej listy
	glNewList(idlisty + 0, GL_COMPILE);
	glTranslatef(0, 0, 10);
	glutWireCube(1);
	glEndList();
	// utworzenie drugiej listy
	glNewList(idlisty + 1, GL_COMPILE);

	//--------------------------------------------------------------- LAB_2 

	int liczba_wierzcholkow = 6;
	float R = 1;
	float x, y;
	float alfa = 0;
	float deltaAlfa = (2 * M_PI) / liczba_wierzcholkow;

	//--------------------------------------- LAB 3 pomocnicze

	// dodanie podlogi (spłaszczona sfera)
	glPushMatrix();
	glColor3f(0.0,1.0,0.0);
	glTranslatef(0.0, -3.0, 0.0);
	glScalef(100.0, 0.1, 100.0);
	glutSolidSphere(1, 100, 100);
	glPopMatrix();

	//ustawienie wektorów normalnych - osobno dla kazdej sciany
	// glNormal3f(0.0, 0.0, 1.0);

	//----------------------------------------------------------

	// wyswietla tylko siatke:
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// nakretka
	glNormal3f(0.0, 0.0, -1.0);
	glColor3f(0.61, 0.13, 0.36);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < liczba_wierzcholkow; i++)
	{
		x = R * sin(alfa);
		y = R * cos(alfa);
		glVertex3f(x, y, 0);
		alfa += deltaAlfa;
	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	alfa = 0;
	for (int i = 0; i < liczba_wierzcholkow + 1; i++)
	{
		x = R * sin(alfa);
		y = R * cos(alfa);
	
		glNormal3f(x, y, 0.0);
		
		glVertex3f(x, y, 0);
		glVertex3f(x, y, 0.3);
		alfa += deltaAlfa;
	}
	glEnd();

	glNormal3f(0.0, 0.0, 1.0);
	glTranslatef(0, 0, 0.3);
	glBegin(GL_TRIANGLE_FAN);
	alfa = 0;
	for (int i = 0; i < liczba_wierzcholkow; i++)
	{
		x = R * sin(alfa);
		y = R * cos(alfa);
		glVertex3f(x, y, 0);
		alfa += deltaAlfa;
	}
	glEnd();

	//glColor3f(1.0, 0.22, 0.78);
	// rurka
	glBegin(GL_TRIANGLE_FAN);
	liczba_wierzcholkow = 100;
	R = 0.3;
	alfa = 0;
	for (int i = 0; i < liczba_wierzcholkow; i++)
	{
		x = R * sin(alfa);
		y = R * cos(alfa);
		glVertex3f(x, y, 0);
		alfa += deltaAlfa;
	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	alfa = 0;
	for (int i = 0; i < liczba_wierzcholkow + 1; i++)
	{
		x = R * sin(alfa);
		y = R * cos(alfa);

		glNormal3f(x, y, 0.0);

		glVertex3f(x, y, 0);
		glVertex3f(x, y, 2);
		alfa += deltaAlfa;
	}
	glEnd();

	glNormal3f(0.0, 0.0, 1.0);
	glTranslatef(0, 0, 2);
	glBegin(GL_TRIANGLE_FAN);
	alfa = 0;
	for (int i = 0; i < liczba_wierzcholkow; i++)
	{
		x = R * sin(alfa);
		y = R * cos(alfa);
		glVertex3f(x, y, 0);
		alfa += deltaAlfa;
	}
	glEnd();

	// druga rurka
	glTranslatef(0, 0, -2.3);
	glBegin(GL_TRIANGLE_FAN);
	liczba_wierzcholkow = 100;
	R = 0.3;
	alfa = 0;
	for (int i = 0; i < liczba_wierzcholkow; i++)
	{
		x = R * sin(alfa);
		y = R * cos(alfa);
		glVertex3f(x, y, 0);
		alfa += deltaAlfa;
	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	alfa = 0;
	for (int i = 0; i < liczba_wierzcholkow + 1; i++)
	{
		x = R * sin(alfa);
		y = R * cos(alfa);

		glNormal3f(x, y, 0.0);

		glVertex3f(x, y, 0);
		glVertex3f(x, y, -2);
		alfa += deltaAlfa;
	}
	glEnd();

	glNormal3f(0.0, 0.0, -1.0);
	glTranslatef(0, 0, -2);
	glBegin(GL_TRIANGLE_FAN);
	alfa = 0;
	for (int i = 0; i < liczba_wierzcholkow; i++)
	{
		x = R * sin(alfa);
		y = R * cos(alfa);
		glVertex3f(x, y, 0);
		alfa += deltaAlfa;
	}
	glEnd();

	// --------------------------------------------------------------------- 

	glColor3f(1, 0, 1);
	glTranslatef(0, 0, 8);
	glutSolidTeapot(1);
	//glutWireTeapot(1);
	glColor3f(1, 1, 0);
	glTranslatef(0, 0, 10);
	glutSolidTeapot(1);
	//glutWireTeapot(1);
	glColor3f(0, 1, 1);
	glTranslatef(0, 0, 10);
	glutSolidTeapot(1);
	//glutWireTeapot(1);
	glEndList();

	// utworzenie trzeciej listy
	glNewList(idlisty + 2, GL_COMPILE);
	glTranslatef(0, 0, 10);
	glutWireCone(1, 1, 10, 10);
	glEndList();

}

void UstawKamere() {
	double cosx, siny, sinx;
	double CelX, CelY, CelZ;
	// wartości funkcji trygonometrycznych
	// obliczamy tylko raz dla oszczędności
	if (KeyDOWN) PredkoscKamery = -0.02;
	if (KeyUP) PredkoscKamery = 0.02;
	if (KeyLEFT) ObrotX -= 0.002;
	if (KeyRIGHT) ObrotX += 0.002;
	siny = sin(ObrotY);
	cosx = cos(ObrotX);
	sinx = sin(ObrotX);
	// nowa pozycja kamery
	eyex += cosx * PredkoscKamery;
	eyey += siny * PredkoscKamery;
	eyez += sinx * PredkoscKamery;
	// punkt wycelowania kamery powinien
	// znajdować się gdzieś "przed jej nosem"
	CelX = eyex + cosx;
	CelY = eyey + siny;
	CelZ = eyez + sinx;
	gluLookAt(eyex, eyey, eyez, CelX, CelY, CelZ, 0, 1, 0);
	//gluLookAt( eyex, eyey, eyez, centerx, centery, centerz, 0, 1, 0 );
	PredkoscKamery = 0;
}

float kat_obrotu_swiatla = 0;

void Display()
{
	// kolor tła - zawartość bufora koloru
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// czyszczenie bufora koloru
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// wybór macierzy modelowania
	glMatrixMode(GL_MODELVIEW);
	// macierz modelowania = macierz jednostkowa
	glLoadIdentity();
	UstawKamere();

	// ustawienie obserwatora
	//glRotatef(kat,1,0,0);
	// przesunięcie obiektu o wektor [0,0,-3]
	//glTranslatef( 0, 0, 2.0 );
	// kolor krawędzi sześcianu
	glColor3f(0.0, 0.0, 0.0);
	// glutWireCube(1);

	switch (figure)
	{
	case 1:
		glCallList(idlisty + 0);
		break;
	case 2:
		glCallList(idlisty + 1);
		break;
	case 3:
		glCallList(idlisty + 2);
		break;
	}

	// skierowanie poleceń do wykonania
	glFlush();
	// zamiana buforów koloru
	glutSwapBuffers();

	// ---------------------------- LAB 3

	glEnable(GL_LIGHTING);
	//GL_LIGHT_MODEL_AMBIENT – określa globalne światło otaczające.
	//GL_LIGHT_MODEL_TWO_SIDE – określa oświetlenie przednich i tylnych ścian.
	//GL_LIGHT_MODEL_LOCAL_VIEWER –modyfikuje obliczanie kąta odbicia dla odbłysków.

	GLfloat ambientlight[] = { 0.02, 0.02, 0.02, 1.0 };
	//ustawia parametry modelu oświetlenia.
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientlight);

	//Ustawiamy teraz właściwości materiału :
	GLfloat gray[] = { 0.75, 0.75, 0.75, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);

	//WłączeniE śledzenia kolorów.
	glEnable(GL_COLOR_MATERIAL);

	//Ustawienie własności otaczającej i rozpraszającej dla przednich stron wielokątów tak aby śledziły wywołania glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	//Teraz określamy normalne do powierzchni.
	glNormal3f(0.0, -1.0, 0.0);
	//Normalne trzeba znormalizować :
	glEnable(GL_NORMALIZE);

	//Ustawiamy właściwości dodanego źródła światła rozpraszającego :
	GLfloat DiffuseLight1[] = { 1.0,1.0,1.0,1.0 };
	GLfloat LightPosition1[] = { 0.0, 1.0, 5.0, 1.0 };
	GLfloat AmbientLight[] = { 0.1, 0.1, 0.1, 1.0 };

	//glLightfv – ustawia parametry światła.
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight1);
	
	// krecenia swiatla
	glPushMatrix();
	glRotatef(kat_obrotu_swiatla, 0.0, 1.0, 0.0);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition1);
	kat_obrotu_swiatla+=0.5;
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);

	//Włączenie konkretnego światła
	glEnable(GL_LIGHT0);
	//Dodanie światła odbłysków :
	GLfloat specular[] = { 0.8,0.8,0.8,1.0 };
	//Ustawienie:
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	//Ustawienie właściwości materiału :
	//Tablica:
	GLfloat specref[] = { 1.0,1.0,1.0,1.0 };
	//Ustawienie:
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	//Określenie stopnia połyskliwości : określa jak mała i skupiona będzie plama połysku
	glMateriali(GL_FRONT, GL_SHININESS, 128);

}

// zmiana wielkości okna
void Reshape(int width, int height)
{
	// obszar renderingu - całe okno
	glViewport(0, 0, width, height);
	// wybór macierzy rzutowania
	glMatrixMode(GL_PROJECTION);
	// macierz rzutowania = macierz jednostkowa
	glLoadIdentity();
	// obliczenie aspektu obrazu z uwzględnieniem
	// przypadku, gdy wysokość obrazu wynosi 0
	GLdouble aspect = 1;
	if (height > 0)
		aspect = width / (GLdouble)height;
	// rzutowanie perspektywiczne
	gluPerspective(fovy, aspect, 0.01, 100.0);
	// generowanie sceny 3D
	Display();
}

// obsługa klawiatury
void Klawisze(unsigned char key, int x, int y)
{
	// klawisz +
	if (key == '+' && fovy < 180)
		fovy++;
	// klawisz -
	if (key == '-' && fovy > 0)
		fovy--;
	if (key == 'a' && fovy > 0)
		kat++;
	if (key == 'w')
		PredkoscKamery = 0.02;
	if (key == 's')
		PredkoscKamery = -0.02;
	if (key == 'e')
		ObrotX += 0.02;
	if (key == 'q')
		ObrotX -= 0.02;
	if (key == 'r')
		ObrotY += 0.02;
	if (key == 'f')
		ObrotY -= 0.02;
	// odrysowanie okna
	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

void KlawiszeSpecjalne(int key, int x, int y)
{
	switch (key)
	{
		// kursor w lewo
	case GLUT_KEY_LEFT:
		eyex += 0.1;
		break;
		// kursor w górę
	case GLUT_KEY_UP:
		eyey -= 0.1;
		break;
		// kursor w prawo
	case GLUT_KEY_RIGHT:
		eyex -= 0.1;
		break;
		// kursor w dół
	case GLUT_KEY_DOWN:
		eyey += 0.1;
		break;
	}
	// odrysowanie okna
	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

// obsługa menu podręcznego
void Menu(int value)
{
	switch (value)
	{
		// wyjście
	case EXIT:
		exit(0);
		// wyjście
	case 1:
		figure = 1;
		break;
	case 2:
		figure = 2;
		break;
	case 3:
		figure = 3;
		break;
	}
	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

void KeyDown(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		KeyUP = true;
		break;
	case GLUT_KEY_DOWN:
		KeyDOWN = true;
		break;
	case GLUT_KEY_LEFT:
		KeyLEFT = true;
		break;
	case GLUT_KEY_RIGHT:
		KeyRIGHT = true;
		break;
	}
}

void KeyUp(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		KeyUP = false;
		break;
	case GLUT_KEY_DOWN:
		KeyDOWN = false;
		break;
	case GLUT_KEY_LEFT:
		KeyLEFT = false;
		break;
	case GLUT_KEY_RIGHT:
		KeyRIGHT = false;
		break;
	}
}

int main(int argc, char * argv[])
{
	// inicjalizacja biblioteki GLUT
	glutInit(&argc, argv);
	// inicjalizacja bufora ramki
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	// rozmiary głównego okna programu
	glutInitWindowSize(400, 400);
	// utworzenie głównego okna programu
#ifdef WIN32
	glutCreateWindow("Sześcian 3");
#else
	glutCreateWindow("Szescian 3");
#endif
	// dołączenie funkcji generującej scenę 3D
	glutDisplayFunc(Display);
	// dołączenie funkcji wywoływanej przy zmianie rozmiaru okna
	glutReshapeFunc(Reshape);
	// dołączenie funkcji obsługi klawiatury
	glutKeyboardFunc(Klawisze);
	// dołączenie funkcji obsługi klawiszy funkcyjnych i klawiszy kursora
	// glutSpecialFunc( KlawiszeSpecjalne );
	glutSpecialFunc(KeyDown);
	glutSpecialUpFunc(KeyUp);
	// utworzenie menu podręcznego
	glutCreateMenu(Menu);
	// dodanie pozycji do menu podręcznego
	glutAddMenuEntry("Wyjście", EXIT);
	glutAddMenuEntry("Rys1", 1);
	glutAddMenuEntry("Rys2", 2);
	glutAddMenuEntry("Rys3", 3);
	// określenie przycisku myszki obsługującej menu podręczne
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	GenerujListyWyswietlania();
	glutIdleFunc(Display);
	// wprowadzenie programu do obsługi pętli komunikatów
	glutMainLoop();
	return 0;
}