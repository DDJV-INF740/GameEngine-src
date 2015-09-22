// Precompiled.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

// check that exactly one of NDEBUG and _DEBUG is defined
#if !(defined NDEBUG ^ defined _DEBUG)
#error Exactly one of NDEBUG and _DEBUG needs to be defined by preprocessor
#endif


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

#include <d3d9.h>
#include <d3dx9mesh.h>
#include <PxPhysicsAPI.h>

#include <vector>
#include <map>

using namespace physx;

#endif // _NOPCH