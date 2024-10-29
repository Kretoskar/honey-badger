#pragma once

#include <bitset>

namespace HoneyBadger
{
	using Entity = uint32_t;
	constexpr Entity MAX_ENTITIES = 320000;

	using ComponentType = std::uint8_t;
	const ComponentType MAX_COMPONENTS = 128;

	using Signature = std::bitset<MAX_COMPONENTS>;
}