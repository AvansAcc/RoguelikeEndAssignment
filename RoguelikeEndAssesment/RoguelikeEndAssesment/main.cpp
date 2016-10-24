#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h> 
#include <crtdbg.h>

#include "RogueLike/RogueLike.h"
#include "RogueLike/Utils/File.h"


void StartGame()
{
	RogueLike::RogueLike r;
	r.Start();
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	StartGame();

	system("PAUSE");

	_CrtDumpMemoryLeaks();
    return 0;
}

