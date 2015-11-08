#pragma once

namespace engine
{

//=============================================================================
// INTERFACE IComponentInterface
//=============================================================================
class IComponentInterface
{
public:
	virtual ~IComponentInterface() {}

public:
	typedef const char* IdType;
	static IdType NullId;
};

} // namespace engine
