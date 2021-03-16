#pragma once

class HorseMeterManager
{
public:
	static void InstallHooks();

private:
	HorseMeterManager() = default;

	static RE::HUDMenu* SetupHUDMenu(void* a_arg1);
	static float GetFillPercent(RE::ActorValueMeter* a_meter);

	inline static REL::Relocation<decltype(SetupHUDMenu)> _SetupHUDMenu;
	inline static REL::Relocation<decltype(GetFillPercent)> _GetFillPercent;
};
