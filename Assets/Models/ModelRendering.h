#pragma once

//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include "Core/Rendering/IRenderPrimitive.h"

namespace engine {

//=============================================================================
// FORWARD DEFINITIONS
//=============================================================================
class IModel;

//=============================================================================
// CLASS ModelRendering
//=============================================================================
class ModelRendering: public IRenderPrimitive
{
private:
	const IModel &_model;

public:
	ModelRendering(const IModel &iModel);
	virtual void render(const GameObjectRef &iGameObject) override;
};
} // namespace engine
