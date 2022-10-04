#include "MainForm.h"

#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace Provisor;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	srand(time(0));
	setlocale(LC_ALL, "rus");
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew MainForm);
	return 0;
}