#include <stdio.h>   //printf
#include <stdlib.h>  //system
#include <Windows.h> //Keys

constexpr int g_LevelSizeX = 8;
constexpr int g_LevelSizeY = 8;

struct SPosition
{
	int m_X;
	int m_Y;
};

char g_Level[g_LevelSizeX * g_LevelSizeY] =
{
	'W','W','W','W','W','W','W','W',
	'D',' ',' ',' ',' ',' ',' ','W',
	'W',' ',' ',' ',' ',' ',' ','W',
	'W','W','W',' ','W','W','W','W',
	'W',' ',' ',' ','W',' ',' ','W',
	'W',' ','W',' ','W','W',' ','W',
	'W','I','W',' ',' ','W','K','W',
	'W','W','W','W','W','W','W','W',

};


SPosition g_PlayerPosition = { 6 , 1 }; //SET START POSITION FOR PLAYER - CURRENTLY MANUAL

void ClearOutput() 
{
	system("cls"); //Clear console
}


void Output(char* _pLevel, int _SizeX, int _SizeY)
{
	for (int y = 0; y < _SizeY; ++y)
	{
		for (int x = 0; x < _SizeX; ++x)
		{
			if (x == g_PlayerPosition.m_X && y == g_PlayerPosition.m_Y)
			{
				printf("P"); //Letter P on current Player Position
			}
			else
			{
				printf("%c", _pLevel[y * _SizeX + x]); //Print Level in Console
			}
		}

		printf("\n");
		
	}
}


int main()
{
	bool ItemCollected = false;
	bool KeyCollected = false;
	bool IsRunning = true;
	for (;IsRunning;) //GAME LOOP
	{
		// Check Input
		// Calculate Game State (aktueller Zustand + neuer Input = neuer Zustand)
		// Output
		

		// MOVEMENT
		if ((GetKeyState(VK_UP) & 0x80) != 0)
		{
			if (g_Level[(g_PlayerPosition.m_Y - 1) * g_LevelSizeX + g_PlayerPosition.m_X] != 'W')
			{
				--g_PlayerPosition.m_Y;
				Sleep(100);
			}
		}

		if ((GetKeyState(VK_DOWN) & 0x80) != 0)
		{
			if (g_Level[(g_PlayerPosition.m_Y + 1) * g_LevelSizeX + g_PlayerPosition.m_X] != 'W')
			{
				++g_PlayerPosition.m_Y;
				Sleep(100);
			}
		}

		if ((GetKeyState(VK_LEFT) & 0x80) != 0)
		{
			if (g_Level[g_PlayerPosition.m_Y * g_LevelSizeX + (g_PlayerPosition.m_X - 1)] != 'W')
			{
				g_PlayerPosition.m_X--;
				Sleep(100);
			}
		}

		if ((GetKeyState(VK_RIGHT) & 0x80) != 0)
		{
			if (g_Level[g_PlayerPosition.m_Y * g_LevelSizeX + (g_PlayerPosition.m_X + 1)] != 'W')
			{
				g_PlayerPosition.m_X++;
				Sleep(100);
			}
			
		}




		//ITEM COLLECTING
		if (g_Level[g_PlayerPosition.m_Y * g_LevelSizeX + g_PlayerPosition.m_X] == 'I')
		{
			ItemCollected = true;
			g_Level[g_PlayerPosition.m_Y * g_LevelSizeX + g_PlayerPosition.m_X] = ' ';
		}

		//ITEM USING - ONLY TO THE RIGHT OF PLAYER  DO: 'P' -> 'W'    DONT: 'W'--'P'  'W'    'P'
		//                                                                             |      |
		//                                                                            'P'    'W'
		if (((GetKeyState(VK_SPACE) & 0x80) != 0) && ItemCollected)
		{
			if (g_Level[g_PlayerPosition.m_Y * g_LevelSizeX + (g_PlayerPosition.m_X + 1)] == 'W'  && g_PlayerPosition.m_Y * g_LevelSizeX + (g_PlayerPosition.m_X + 1) != 15 && g_PlayerPosition.m_Y * g_LevelSizeX + (g_PlayerPosition.m_X + 1) != 23)
			{
				g_Level[g_PlayerPosition.m_Y * g_LevelSizeX + (g_PlayerPosition.m_X + 1)] = ' ';
				ItemCollected = false;
			}
		}

		//KEY COLLECTING
		if (g_Level[g_PlayerPosition.m_Y * g_LevelSizeX + g_PlayerPosition.m_X] == 'K')
		{
			KeyCollected = true;
			g_Level[g_PlayerPosition.m_Y * g_LevelSizeX + g_PlayerPosition.m_X] = ' ';
		}

		

		// CLOSE PROGRAM
		if ((GetKeyState(VK_ESCAPE) & 0x80) != 0)
		{
			IsRunning = false;
		}



		//OUTPUT LEVEL-ARRAY
		ClearOutput();
		Output(g_Level, g_LevelSizeX, g_LevelSizeY);
		
		//END LEVEL
		if (g_Level[g_PlayerPosition.m_Y * g_LevelSizeX + g_PlayerPosition.m_X] == 'D' && KeyCollected)
		{
			//NEXT LEVEL
			//LEVEL END
			printf("CONCRATS YOU FOUND THE EXIT");
			Sleep(1000);
			IsRunning = false;
		}



	}
	return 0;
}
