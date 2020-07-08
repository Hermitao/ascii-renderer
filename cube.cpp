#include <windows.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <utility>

HANDLE stdOut = GetStdHandle(STD_OUTPUT_HANDLE);

/// <summary>Set cursor position.</summary>
void goToxy(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	
	if (!SetConsoleCursorPosition(stdOut, coord))
	{

	}
}

/// <summary>Write text at cursor.</summary>
void write(char *message)
{
	DWORD written{0};
	WriteConsole(stdOut, message, strlen(message), &written, NULL);
}

/// <summary>Combines goToxy and write.</summary>
void writeAt(int column, int line, char *character)
{
	goToxy(column, line);
	write(character);
}	

void drawLineMajorAxis(int x, int y, int majorAxis, int majorAxisMovement, int minorAxisMovement, int dx, int dy, char *character)
{
	const int dx2 {dx * 2};
	const int dy2 {dy * 2};
	const int dy2Mindx2 {dy2 - dx2};

	int Error {dy2 - dx};

	char debugText[]{"drawLineMajorAxis()"};
	writeAt(0, 0, debugText);

	writeAt(x, y, character);
	while (dx--)
	{
		if (Error > 0)
		{
			if (majorAxis == 0)
			{
				x += majorAxisMovement;
				y += minorAxisMovement;
			}	
			else
			{
				x += minorAxisMovement;
				y += majorAxisMovement;
			}
			Error += dy2Mindx2;
		}

		else
		{
			if (majorAxis == 0)
			{
				x += majorAxisMovement;
			}	
			else
			{
				y += majorAxisMovement;
			}
			Error += dy2;
		}

		writeAt(x, y, character);
	}
}

void drawLineSingleAxis(int x, int y, int majorAxis, int majorAxisMovement, int dx, char *character)
{
	writeAt(x, y, character);

	char debugText[]{"drawLineSingleAxis()"};
	writeAt(0, 0, debugText);

	while (dx--)
	{
		if (majorAxis == 0)
			{
				x += majorAxisMovement;
			}	
			else
			{
				y += majorAxisMovement;
			}
		writeAt(x, y, character);
	}
}

/// <summary>Draw a line of text via Bresenham's line algorithm.</summary>
void drawLine (int x1, int y1, int x2, int y2, char *character)
{
	int dx {x2 - x1};
	int dy {y2 - y1};

	// if X is the major axis
	if (abs(dx) >= abs(dy))
	{
		if (dx < 0)
		{
			dx *= -1;
			dy *= -1;
			std::swap(x1, x2);
			std::swap(y1, y2);
		}

		if (dy > 0)
			drawLineMajorAxis(x1, y1, 0, 1, 1, dx, dy, character);
		else if (dy < 0)
			drawLineMajorAxis(x1, y1, 0, 1, -1, dx, -dy, character);
		else
			drawLineSingleAxis(x1, y1, 0, 1, dx, character);
	}	
	// if Y is the major axis
	else
	{
		if (dy < 0)
		{
			dx *= -1;
			dy *= -1;
			std::swap(x1, x2);
			std::swap(y1, y2);
		}

		if (dx > 0)
			drawLineMajorAxis(x1, y1, 1, 1, 1, dy, dx, character);
		else if (dx < 0)
			drawLineMajorAxis(x1, y1, 1, 1, -1, dy, -dx, character);
		else
			drawLineSingleAxis(x1, y1, 1, 1, dy, character);
		
	}


}

int main()
{
	system("color 04");
	system("cls");

	char c[]{"+"};
	
	double originx {30.0};
	double originy {20.0};

	float i{0.0f};
	while (1)
	{
		system("cls");
		//drawLine(static_cast<int>((cos(i/1.5f)/2.0 + 0.5) * 70 + 1), static_cast<int>((sin(i)/2.0 + 0.5) * 12 + 1), 150, static_cast<int>((sin(i)/2.0 + 0.5) * 40.0f + 2.0f), c); 	
		drawLine(static_cast<int>(sin(i) * 15.0 * 2 + originx), static_cast<int>(cos(i) * 15.0 + originy), static_cast<int>(originx), static_cast<int>(originy), c); 
		i += 0.05f;	
		Sleep(15);
	}

	return 0;
}
