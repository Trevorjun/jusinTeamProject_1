#ifndef PCH_H
#define PCH_H

#include "framework.h"
#include <list>
#include <algorithm>
using namespace std;

// custom header
#include "Vector2.h"

#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
	#ifndef DBG_NEW 
		#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
		#define new DBG_NEW 
	#endif
#endif

#endif //PCH_H
