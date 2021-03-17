#include "HorseMeterManager.h"
#include "Offsets.h"

void HorseMeterManager::InstallHooks()
{
	static REL::Relocation<std::uintptr_t> hook{ Offset::HUDMenu_ctor, 0x5D };
	auto& trampoline = SKSE::GetTrampoline();
	_SetupHUDMenu = trampoline.write_call<5>(hook.address(), SetupHUDMenu);

	static REL::Relocation<std::uintptr_t> vtbl{ Offset::ActorValueMeter_Vtbl };
	_GetFillPercent = vtbl.write_vfunc(0x6, GetFillPercent);
	logger::info("Installed hook for horse stamina meter"sv);
}

RE::HUDMenu* HorseMeterManager::SetupHUDMenu(void* a_arg1)
{
	auto menu = _SetupHUDMenu(a_arg1);

	if (menu)
	{
		RE::GFxValue stamina;
		menu->root.GetMember("Stamina", &stamina);
		stamina.SetMember("HorseMode", true);
	}

	return menu;
}

float HorseMeterManager::GetFillPercent(RE::ActorValueMeter* a_meter)
{
	auto player = RE::PlayerCharacter::GetSingleton();
	if (a_meter->actorValue == RE::ActorValue::kStamina && player && player->IsOnMount())
	{
		static REL::Relocation<int(RE::Actor*, RE::ActorPtr*)> getMount{ Offset::Actor_GetMount };
		RE::ActorPtr mount = nullptr;
		getMount(player, &mount);

		if (mount)
		{
			auto currentValue = mount ? mount->GetActorValue(a_meter->actorValue) : 0.0f;
			auto maxValue = mount ? mount->GetPermanentActorValue(a_meter->actorValue) : 0.0f;

			if (maxValue == 0.0f)
			{
				return 0.0f;
			}
			else
			{
				return (currentValue / maxValue) * 100.0f;
			}
		}
	}

	return _GetFillPercent(a_meter);
}