#pragma once
namespace engine
{

//=============================================================================
// INTERFACE IGameInterface
//=============================================================================
class IGameInterface
{
public:
	virtual ~IGameInterface() {}

public:
	typedef const char* IdType;
	static IdType NullId;
};
} // namespace engine
