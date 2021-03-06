#pragma once

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Rendering/IRenderPrimitive.h"

namespace engine {

//=============================================================================
// FORWARD DECLARATIONS
//=============================================================================
class HeightMapRenderData;

//=============================================================================
// CLASS Terrain
//=============================================================================
class HeightMapRendering: public IRenderPrimitive
{
public:
	HeightMapRendering(HeightMapRenderData *iData);

public:
	virtual void render(const GameObjectRef &iGameObject) override;

private:
	HeightMapRenderData *_data;
};
} // namespace engine

