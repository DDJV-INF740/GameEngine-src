// Precompiled.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"
#include <cassert>

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#define SAFE_RELEASE(_x) { (_x)->Release(); (_x) = nullptr; }

#ifdef _DEBUG
#define ASSERT(x) assert(x)
#else
#define ASSERT(x) do { } while (false)
#endif

#ifndef _NOPCH

// TODO: reference additional headers your program requires here

#endif // _NOPCH

