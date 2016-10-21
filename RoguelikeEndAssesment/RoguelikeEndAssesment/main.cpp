// main.cpp : Defines the entry point for the console application.
#include "stdafx.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "RogueLike/RogueLike.h"
#include "RogueLike/Model/Level.h" // Klopt dit met die slashes?


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	RogueLike::RogueLike r;
	r.Start();

	system("PAUSE");

	_CrtDumpMemoryLeaks();
    return 0;
}

