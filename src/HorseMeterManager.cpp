#include "HorseMeterManager.h"
#include "Offsets.h"

void HorseMeterManager::InstallHooks()
{
	// SkyrimVR 1.4.15.1: 0x8B3940 + 0x5D
	// SkyrimSE 1.6.318.0: 0x8B6350 + 0x5D
	std::uintptr_t hookAddr = Offset::MenuManager::CreateHUDMenu.address() + 0x5D;

	auto& trampoline = SKSE::GetTrampoline();
	_SetupHUDMenu = trampoline.write_call<5>(hookAddr, SetupHUDMenu);

	static REL::Relocation<std::uintptr_t> vtbl{ Offset::ActorValueMeter::Vtbl };
	_GetFillPercent = vtbl.write_vfunc(0x6, GetFillPercent);
	logger::info("Installed hook for horse stamina meter"sv);
}

bool HorseMeterManager::GetMount(RE::Actor* a_actor, RE::ActorPtr* a_mountOut)
{
	using func_t = decltype(&GetMount);
	REL::Relocation<func_t> func{ Offset::Actor::GetMount };
	return func(a_actor, a_mountOut);
}

RE::HUDMenu* HorseMeterManager::SetupHUDMenu(void* a_arg1)
{
	auto menu = _SetupHUDMenu(a_arg1);

	if (menu) {
		RE::GFxValue stamina;
		menu->root.GetMember("Stamina", &stamina);

		if (stamina.IsObject()) {
			stamina.SetMember("HorseMode", true);
		}
	}

	return menu;
}

float HorseMeterManager::GetFillPercent(RE::ActorValueMeter* a_meter)
{
	auto player = RE::PlayerCharacter::GetSingleton();
	if (a_meter->actorValue == RE::ActorValue::kStamina && player && player->IsOnMount()) {
		RE::ActorPtr mount;
		GetMount(player, &mount);

		if (mount) {
			auto currentValue = mount ? mount->GetActorValue(a_meter->actorValue) : 0.0f;
			auto maxValue = mount ? mount->GetPermanentActorValue(a_meter->actorValue) : 0.0f;

			if (maxValue == 0.0f) {
				return 0.0f;
			}
			else {
				return (currentValue / maxValue) * 100.0f;
			}
		}
	}

	return _GetFillPercent(a_meter);
}
