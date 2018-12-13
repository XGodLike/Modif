#pragma once
#if _DEBUG
	#include "vld.h"
#endif

#include <Windows.h>
#include <time.h>
#include <string>
#include <map>
#include <vector>
#include "resource.h"

#include "../json/include/json/json.h"
using namespace std;


#define MODIF_LOCAL "modif_local.dll"
#define MAX_SIZE 256