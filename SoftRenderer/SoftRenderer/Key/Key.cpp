#include "Key.h"

bool* bTurn = nullptr;
bool* bMove = nullptr;
bool bWillExit = false;


void initKeys()
{
	bTurn = new bool[4];
	memset(bTurn, 0, 4 * sizeof(bool));

	bMove = new bool[6];
	memset(bMove, 0, 6 * sizeof(bool));
}

void releaseKeys()
{
	delete[] bTurn; bTurn = nullptr;
	delete[] bMove; bMove = nullptr;
}

void keyDown(int key)
{
	switch (key)
	{
	case 'W':
		bMove[0] = true;
		break;

	case 'S':
		bMove[1] = true;
		break;

	case 'A':
		bMove[2] = true;
		break;

	case 'D':
		bMove[3] = true;
		break;

	case KEY_SPACE:
		bMove[4] = true;
		break;

	case 'Z':
		bMove[5] = true;
		break;

	case KEY_UP:
		bTurn[0] = true;
		break;

	case KEY_DOWN:
		bTurn[1] = true;
		break;

	case KEY_LEFT:
		bTurn[2] = true;
		break;

	case KEY_RIGHT:
		bTurn[3] = true;
		break;
	}
}

void keyUp(int key)
{
	switch (key)
	{
	case 'W':
		bMove[0] = false;
		break;

	case 'S':
		bMove[1] = false;
		break;

	case 'A':
		bMove[2] = false;
		break;

	case 'D':
		bMove[3] = false;
		break;

	case KEY_SPACE:
		bMove[4] = false;
		break;

	case 'Z':
		bMove[5] = false;
		break;

	case KEY_UP:
		bTurn[0] = false;
		break;

	case KEY_DOWN:
		bTurn[1] = false;
		break;

	case KEY_LEFT:
		bTurn[2] = false;
		break;

	case KEY_RIGHT:
		bTurn[3] = false;
		break;

	case KEY_ESCAPE:
		bWillExit = true;
		break;
	}
}
