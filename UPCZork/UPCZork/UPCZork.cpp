#include "stdafx.h"

#include <iostream>
#include <string>
#include <vector>
#include <conio.h>

#include "Common.h"
#include "World.h"

using namespace std;

int main()
{
	World myWorld;

	char keyPressed;
	string playerInput;
	vector<string> args;

	cout << "\n  WELCOME TO [GAME NAME]";
	Help();
	cout << "> ";
	StartInput();

	while (1)
	{
		if (_kbhit() != 0)
		{
			keyPressed = _getch();
			if (keyPressed == '\b')
			{
				if (playerInput.length() > 0)
				{
					playerInput.pop_back();
					cout << '\b';
					cout << " ";
					cout << '\b';
				}
			}
			else if (keyPressed != '\r')
			{
				playerInput += keyPressed;
				cout << keyPressed;
			}
			else
			{
				EndInput();

				const char * str = playerInput.c_str();

				do
				{
					const char * begin = str;

					while (*str != ' ' && *str)
						str++;

					args.push_back(string(begin, str));
				} while (0 != *str++);
			}
		}

		if (args.size() > 0 && Equals(args[0], "quit"))
			break;
		if (args.size() > 0 && Equals(args[0], "help"))
			Help();
		if (args.size() > 0 && Equals(args[0], "hi") || args.size() > 0 && Equals(args[0], "hello"))
			cout << "\n\n Hi!\n\n";
		else if (myWorld.Action(args) == false)
			cout << "\n Sorry, I do not understand your command.\n\n";

		if (args.size() > 0)
		{
			args.clear();
			playerInput = "";
			cout << "> ";
			StartInput();
		}

	}

    return 0;
}
