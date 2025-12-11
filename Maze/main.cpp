/*
	GPF Week 6 - Maze Start Code
*/

#include <iostream>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <fstream>
#include <random>

#include "Framework.h"
using namespace std;



// Screen dimensions
int gScreenWidth{ 800 };
int gScreenHeight{ 600 };

// Delay to slow things down
int gTimeDelayMS{ 100 };

// Maze size as constants
constexpr int kMazeColumnsX{ 20 };
constexpr int kMazeRowsY{ 20 };

/*
	2 Dimensional Arrays
	You can think of these as being an array of arrays

	The maze has kMazeColumnsX columns across (20 by default) represented by an array
	We then have kMazeRowsY (20) of these arrays, one for each row

	Columns and rows can be confusing so we tend to prefer working with x and y
	x is the horizontal axis (columns) across and y is the vertical axis (rows) down.

	Each single item is called a cell.

	E.g. to output the value of the cell at 16 X (column 16) and 1 Y (row 1) we would write:
	cout << map[1][16] << endl; // outputs G
*/



//NOTE TO SELF - remember its set up y then x for some reason.
char map[kMazeRowsY][kMazeColumnsX] = {
	// 20 columns (x axis) by 20 rows (y axis)
	// X0   X1   X2   X3   X4   X5   X6   X7   X8   X9   X10  X11  X12  X13  X14  X15  X16  X17  X18  X19 
	{ 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },	//Y0
	{ 'W', '.', '.', '.', '.', 'W', '.', '.', '.', 'W', 'W', '.', '.', '.', '.', 'W', 'G', '.', '.', 'W' },	//Y1
	{ 'W', '.', 'W', 'W', 'W', 'W', 'W', 'W', '.', 'W', '.', '.', 'W', 'W', 'W', 'W', 'W', 'W', '.', 'W' },	//Y2
	{ 'W', '.', 'W', '.', '.', '.', 'W', '.', '.', 'W', '.', 'W', 'W', '.', 'W', '.', '.', '.', '.', 'W' },	//Y3
	{ 'W', '.', 'W', '.', 'W', '.', 'W', '.', 'W', 'W', '.', 'W', 'W', '.', 'W', 'W', 'W', '.', 'W', 'W' },	//Y4
	{ 'W', '.', 'W', '.', 'W', '.', '.', '.', '.', '.', '.', '.', 'W', '.', 'W', '.', '.', '.', '.', 'W' },	//Y5
	{ 'W', '.', 'W', '.', 'W', 'W', 'W', '.', '.', 'W', 'W', '.', 'W', '.', 'W', '.', 'W', '.', '.', 'W' },	//Y6
	{ 'W', '.', 'W', '.', 'W', '.', 'W', 'W', 'W', 'W', 'W', '.', 'W', '.', 'W', '.', 'W', 'W', 'W', 'W' },	//Y7
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W', '.', '.', '.', 'W', '.', '.', '.', '.', 'W' },	//Y8
	{ 'W', '.', 'W', '.', 'W', '.', 'W', 'W', '.', 'W', 'W', 'W', '.', 'W', 'W', 'W', 'W', '.', 'W', 'W' },	//Y9
	{ 'W', '.', 'W', 'W', 'W', 'W', 'W', 'W', '.', 'W', 'W', 'W', '.', 'W', '.', 'W', 'W', '.', 'W', 'W' },	//Y10
	{ 'W', '.', '.', '.', '.', 'W', '.', '.', '.', 'W', 'W', '.', '.', '.', '.', 'W', '.', '.', '.', 'W' },	//Y11
	{ 'W', '.', 'W', 'W', 'W', 'W', 'W', 'W', '.', '.', '.', '.', 'W', '.', 'W', 'W', 'W', 'W', '.', 'W' },	//Y12
	{ 'W', '.', 'W', '.', '.', '.', 'W', '.', '.', 'W', 'W', '.', 'W', '.', 'W', '.', '.', '.', '.', 'W' },	//Y13
	{ 'W', '.', 'W', '.', 'W', '.', 'W', '.', 'W', 'W', 'W', '.', 'W', '.', 'W', '.', 'W', 'W', 'W', 'W' },	//Y14
	{ 'W', '.', 'W', '.', 'W', '.', '.', '.', '.', '.', 'W', '.', 'W', '.', 'W', '.', '.', '.', 'W', 'W' },	//Y15
	{ 'W', '.', 'W', '.', 'W', 'W', 'W', '.', '.', 'W', 'W', '.', 'W', '.', '.', '.', 'W', '.', '.', 'W' },	//Y16
	{ 'W', '.', 'W', '.', 'W', '.', 'W', 'W', 'W', 'W', '.', '.', 'W', 'W', 'W', '.', 'W', 'W', '.', 'W' },	//Y17
	{ 'W', '.', '.', '.', '.', '.', '.', '.', '.', 'W', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'W' },	//Y18
	{ 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },	//Y19
};

//Using the screen dimensions and dividing them into rows/columns to create cell sizes.
int cellWidth = gScreenWidth / kMazeColumnsX;
int cellHeight = gScreenHeight / kMazeRowsY;

//Map array is globally defined - no need to pass it as a param to this func. 
void DrawMaze()
{


	//Creating variables to store top left corner of cell coords. These are updated in the loops.
	int positionX = 0;
	int positionY = 0;

	//Using nested loops. Going through and drawing vertically, resetting y, then moving onto next
	//X value and drawing vertically again. Colour of cell is predermined before drawing of cell.
	for (int counter = 0; counter < kMazeColumnsX; counter++) {

		for (int i = 0; i < kMazeRowsY; i++) {
			switch (map[i][counter]) {
			case 'W':
				ChangeColour(0, 0, 0);
				break;
			case '.':
				ChangeColour(255, 255, 255);
				break;
			case 'P':
				ChangeColour(0, 0, 255);
				break;
			case 'G':
				ChangeColour(255, 0, 0);
				break;
			default:
				break;
			}

			DrawRectangle(positionX, positionY, cellWidth, cellHeight);
			positionY += cellHeight;
		}
		positionY = 0;
		positionX += cellWidth;
	}
}

//Player Coords.
int playerX;
int playerY;

char playerPosition = map[playerY][playerX];

//This function finds player location as it is currently.
void FindPlayer()
{
	bool looping = true;
	//Adding 'looping == true' to the condiitons for the loop allows us to break from 
	//looping once the player is found.
	for (int counter = 0; counter < kMazeColumnsX && looping; counter++) {

		for (int i = 0; i < kMazeRowsY && looping; i++) {

			if (map[i][counter] == 'P') {
				playerX = counter;
				playerY = i;
				cout << "Player location is " << i << ", " << counter << endl;
				looping = false;

			}
		}
	}
}

int score;

int ResetScore(int& s)
{
	s = 0;
	return s;
}

int SetScore(int& s)
{
	s += 1;
	return s;
}

//Simple check to see if cell being moved to is the goal.
bool CheckIfWon(int x, int y, int& s)
{
	bool won = false;
	if (map[y][x] == 'G')
	{
		SetScore(s);

		float timeTaken = GetElapsedTime();

		cout << "Time: " << timeTaken << " seconds" << endl;
		cout << "Score: " << s << endl;

		won = true;
		return won;
	}
	return won;
}


//Function that sets a new goal character in the map array when previous goal is found.
void NewGoalPosition()
{
	int newX = rand() % 19;
	int newY = rand() % 19;
	bool positionFound = false;
	while (!positionFound)
	{
		if (map[newY][newX] != 'W' && map[newY][newX] != 'P')
		{
			map[newY][newX] = 'G';
			positionFound = true;
		}
		else
		{
			newX = rand() % 19;
			newY = rand() % 19;
		}
	}
}

//Simple check to see if cell being moved to is a wall.
bool CanMoveThere(int x, int y) {
	if (map[y][x] != 'W') {
		return true;
	}
	else if (map[y][x] == 'W') {
		return false;
	}
}


void SavePlayer(int x, int y)
{
	ofstream fileOutput("SavePlayer.txt");
	if (fileOutput.fail())
	{
		cerr << "Could not open file for write";
	}

	cout << "reached" << endl;
	fileOutput << x << " " << y << endl;
	fileOutput.close();
}

void LoadPlayer(int& x, int& y)
{
	ifstream input("SavePlayer.txt");
	if (!input) {
		cerr << "Could not open file" << endl;
	}
	//testing
	cout << "got it" << endl;
	//wipe current player loc stored in map.
	map[y][x] = '.';
	//read in values into variables.
	input >> x >> y;
	//apply new player loc from file.
	map[y][x] = 'P';
	input.close();
}


void SaveMaze()
{
	ofstream mazeOutput("Maze1.txt");
	if (!mazeOutput)
	{
		cerr << "Could not open file for write";
	}

	//Goes horizontally across, each time 1 is added to Y, the loop within it loops 19 times, completing
	//a horizontal column as named in the variable. Then, after this it means a row is complete, so add a
	//new line character to the text file. Now we go down a row, vertically, and the x loop reinitiates 
	//and once again loops 19 times from 0 for another full column to be completed. 
	for (int i = 0; i < kMazeRowsY; i++)
	{
		for (int counter = 0; counter < kMazeColumnsX; counter++)
		{
			mazeOutput << map[i][counter] << " ";
		}
		mazeOutput << "\n";
	}
	mazeOutput.close();

}

void LoadMaze()
{
	ifstream mazeInput("Maze1.txt");
	if (!mazeInput)
	{
		cerr << "Unable to read file" << endl;
	}
	char charVal;
	for (int i = 0; i < kMazeRowsY; i++)
	{

		for (int counter = 0; counter < kMazeColumnsX; counter++)
		{
			mazeInput >> charVal;
			cout << charVal << " ";
			map[i][counter] = charVal;
		}
		cout << "\n";
	}

}

void PlayerInput(int x, int y) {
	//Creating what happens when each key is pressed, e.g movement in a certain direction.
	EKeyPressed key = GetLastKeyPressed();
	switch (key)
	{
	case EKeyPressed::eNone:
		break;
	case EKeyPressed::eLeft:
		//After each key press, before overwriting any cells, I check to see if the cell
		//being moved to is the goal. If the check for goal returns true, 
		//we form a new goal, then the code for moving the player executes and the old goal is
		//overwritten.
		if (CanMoveThere(playerX - 1, playerY)) 
		{
			if (CheckIfWon(playerX - 1, playerY, score)) 
			{
				NewGoalPosition();
			}
			map[playerY][playerX] = '.';
			playerX--;
			map[playerY][playerX] = 'P';
			cout << playerX << ", " << playerY << endl;
		}
		break;
	case EKeyPressed::eUp:
		if (CanMoveThere(playerX, playerY - 1)) 
		{
			if (CheckIfWon(playerX, playerY - 1, score)) 
			{
				NewGoalPosition();
			}
			map[playerY][playerX] = '.';
			playerY--;
			map[playerY][playerX] = 'P';
			cout << playerX << ", " << playerY << endl;
		}
		break;
	case EKeyPressed::eRight:
		if (CanMoveThere(playerX + 1, playerY)) 
		{
			if (CheckIfWon(playerX + 1, playerY, score)) 
			{
				NewGoalPosition();
			}
			map[playerY][playerX] = '.';
			playerX++;
			map[playerY][playerX] = 'P';
			cout << playerX << ", " << playerY << endl;
		}
		break;
	case EKeyPressed::eDown:
		if (CanMoveThere(playerX, playerY + 1)) 
		{
			if (CheckIfWon(playerX, playerY + 1, score)) 
			{
				NewGoalPosition();
			}
			map[playerY][playerX] = '.';
			playerY++;
			map[playerY][playerX] = 'P';
			cout << playerX << ", " << playerY << endl;
		}
		break;
	case EKeyPressed::eSave:
	{
		SavePlayer(playerX, playerY);
		SaveMaze();
		break;
	}
	case EKeyPressed::eLoad:
	{
		LoadPlayer(playerX, playerY);
		LoadMaze();
		break;
	}
	default:
		break;
	}
}

void RandomPlayerStart()
{
	bool looping = true;

	while (looping)
	{
		int x = rand() % 20;
		int y = rand() % 20;

		if (map[y][x] == '.')
		{
			map[y][x] = 'P';
			looping = false;
		}
	}
}

void LevelSelect()
{
	string levelInput;

}


int main()
{
	srand(time(0));

	ResetScore(score);

	RandomPlayerStart();

	FindPlayer();

	/* Start timer outside loop so it doesnt get restarted constantly */
	StartClock();

	while (UpdateFramework())
	{
		/* Update the maze */
		DrawMaze();

		/* Handles movement input, File saving/loading input, 
		checking cells being moved to for various things too */
		PlayerInput(playerX, playerY);

	}

	return 0;
}

