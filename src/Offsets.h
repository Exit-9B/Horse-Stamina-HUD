#pragma once

namespace Offset
{
#ifndef SKYRIMVR
	namespace Actor
	{
		// SkyrimSE 1.6.318.0: 0x6546F0
		constexpr REL::ID GetMount(38702);
	}

	namespace ActorValueMeter
	{
		// SkyrimSE 1.6.318.0: 0x17A58B8
		constexpr REL::ID Vtbl(215373);
	}

	namespace MenuManager
	{
		// SkyrimSE 1.6.318.0: 0x8B6350
		constexpr REL::ID CreateHUDMenu(51730);
	}

#else

	namespace Actor
	{
		constexpr REL::Offset GetMount(0x637A90);
	}

	namespace ActorValueMeter
	{
		constexpr REL::Offset Vtbl(0x1736C80);
	}

	namespace MenuManager
	{
		constexpr REL::Offset CreateHUDMenu(0x8B3940);
	}
#endif
}
