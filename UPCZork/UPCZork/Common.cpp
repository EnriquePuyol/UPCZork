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
	cout << "\n\n This will be the ";
	StartKeyWord();
	cout << "HELP ";
	EndKeyWord();
	cout << "text\n\n";

	// Go [direction]
	// Look : room
	// Look [item/enemy]
	// Pick [item]
	// Drop [item]
	// Use  [item]
	// Attack [enemy] : no weapon
	// Attack [enemy] with [weapon]
	// Examine: Mirar un obj de tu inventario
	// Inventory

}