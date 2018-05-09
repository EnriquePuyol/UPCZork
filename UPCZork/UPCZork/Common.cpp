#include "stdafx.h"
#include "Common.h"

bool Equals(const string& a, const string& b)
{
	return _stricmp(a.c_str(), b.c_str()) == 0;
}

void StartKeyWord()
{
	HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 2);
}

void EndKeyWord()
{
	HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 7);
}

void StartInput()
{
	HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 6);
}

void EndInput()
{
	HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 7);
}

void Help()
{
	cout << "\n\n Available commands:\n";

	cout << "\n 1. ";
	StartKeyWord();
	cout << "Go ";
	EndKeyWord();
	cout << "+ [direction] -> Move between rooms";

	cout << "\n\n 2. ";
	StartKeyWord();
	cout << "Look ";
	EndKeyWord();
	cout << "-> Look the actual room";
	cout << "\n         + [direction] -> Look the room of that direction";
	cout << "\n         + [item/enemy] -> Look an item or an enemy";

	cout << "\n\n 3. ";
	StartKeyWord();
	cout << "Pick ";
	EndKeyWord();
	cout << "\n         + [item] -> Pick an item from the room";
	cout << "\n         + [item] from [item/enemy] -> Pick an item from an item or an enemy";

	cout << "\n\n 4. ";
	StartKeyWord();
	cout << "Examine ";
	EndKeyWord();
	cout << "+ [item] -> Look the stats of an item from your inventory";

	cout << "\n 5. ";
	StartKeyWord();
	cout << "Drop ";
	EndKeyWord();
	cout << "+ [item] -> Drop an item from your inventory";

	cout << "\n 6. ";
	StartKeyWord();
	cout << "Use ";
	EndKeyWord();
	cout << "+ [item] -> Use an item from your inventory";

	cout << "\n 7. ";
	StartKeyWord();
	cout << "Inventory ";
	EndKeyWord();
	cout << "-> Look all the items of your inventory";

	cout << "\n 8. ";
	StartKeyWord();
	cout << "Stats ";
	EndKeyWord();
	cout << "-> Look at your own stats (does not count weapon damage)";

	cout << "\n 9. ";
	StartKeyWord();
	cout << "Attack ";
	EndKeyWord();
	cout << "+ [enemy] with [weapon] -> Attack an enemy";

	cout << "\n 10. ";
	StartKeyWord();
	cout << "Unlock ";
	EndKeyWord();
	cout << "+ [item/door] with [item] -> Unlock/Open something";

	cout << "\n 11. ";
	StartKeyWord();
	cout << "Equip ";
	EndKeyWord();
	cout << "+ [armour] -> Equip an armour";

	cout << "\n 12. ";
	StartKeyWord();
	cout << "Unequip ";
	EndKeyWord();
	cout << "+ [armour] -> Unequip an armour";

	cout << "\n\n";
}