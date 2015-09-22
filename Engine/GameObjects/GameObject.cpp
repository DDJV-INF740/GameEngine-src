//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Precompiled.h"
#include "GameObject.h"

//=============================================================================
// CLASS GameObject
//=============================================================================
const char* GameObjectBase::debugName() const 
{
	static char name[256] = {0};
	sprintf_s(name, sizeof(name), "%s-0x%08X", typeId(), (int)this);
	return name;
}

