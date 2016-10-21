#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h> 
#include <crtdbg.h>
#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG

#include "RogueLike/RogueLike.h"


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	//RogueLike::RogueLike r;
	//r.Start();

	RogueLike::RogueLike* r = new RogueLike::RogueLike();
	r->Start();

	delete r;

	system("PAUSE");

	_CrtDumpMemoryLeaks();
    return 0;
}

