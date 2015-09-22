#pragma once
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


