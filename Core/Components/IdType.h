#pragma once
//=============================================================================
// EXTERNAL DECLARATIONS
//=============================================================================
#include <cstring>
#include <cstdint>
#include <cstddef>
#include <string>

//#define USE_CRC32_ID

#if defined(USE_CRC32_ID)
#include "Core/crc32.h"
#endif // USE_CRC32_ID

namespace engine
{
struct IdType
{
public:
#if defined(USE_CRC32_ID)
	uint32_t id;
#else
	const char* id;
	size_t _len;
#endif // USE_CRC32_ID

#if defined(USE_CRC32_ID) == false
	constexpr IdType(const char *id, size_t len)
		: id(id)
		, _len(len)
	{}
#endif // USE_CRC32_ID

	template<size_t N>
	constexpr IdType(const char (&id)[N])
#if defined(USE_CRC32_ID)
		: id(constexpr_crc32(id, N))
#else
		: id(id)
		, _len(N-1)
#endif // USE_CRC32_ID
	{}

	constexpr IdType(const IdType &rhs)
#if defined(USE_CRC32_ID)
		: id(rhs.id)
#else
		: IdType(rhs.id, rhs._len)
#endif // USE_CRC32_ID
	{}

	constexpr IdType(nullptr_t ignored)
#if defined(USE_CRC32_ID)
		: id(0)
#else
		: id(nullptr)
		, _len(0)
#endif // USE_CRC32_ID
	{}

	IdType& operator=(const IdType &rhs)
	{
		id = rhs.id;
	}

	bool operator==(const IdType &rhs) const
	{
#if defined(USE_CRC32_ID)
		return id == rhs.id;
#else
#endif // USE_CRC32_ID
	}

	bool operator<(const IdType &rhs) const
	{
#if defined(USE_CRC32_ID)
		return id < rhs.id;
#else
		return std::strcmp(id, rhs.id) < 0;
#endif // USE_CRC32_ID
	}

	std::string toString() const
	{
#if defined(USE_CRC32_ID)
		char buffer[32];
		_itoa_s(id, buffer, 10);
		return buffer;
#else
		return id;
#endif // USE_CRC32_ID
	}

};

static constexpr IdType NullId = nullptr;

} // namespace engine
