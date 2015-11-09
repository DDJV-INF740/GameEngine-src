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
	using IdType = const char*;
	static IdType NullId;
};

} // namespace engine
