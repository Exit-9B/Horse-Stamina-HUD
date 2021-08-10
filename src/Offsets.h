#pragma once

namespace Offset
{
#ifndef SKYRIMVR
	constexpr REL::ID Actor_GetMount{ 37757 };
	constexpr REL::ID HUDMenu_ctor{ 50854 };
	constexpr REL::ID ActorValueMeter_Vtbl{ 551778 };
#else
	constexpr REL::Offset Actor_GetMount{ 0x00637A90 };
	constexpr REL::Offset HUDMenu_ctor{ 0x008B3940 };
	constexpr REL::Offset ActorValueMeter_Vtbl{ 0x01736C80 };
#endif
}
