// main.cpp : Defines the entry point for the console application.
//
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "stdafx.h"
#include "RogueLike/Model/Level.h"


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	/*// Debug
	using namespace RogueLike;
	using namespace Model;
	Level* l = new Level(5,5,0);
	system("PAUSE");*/

    return 0;
}

