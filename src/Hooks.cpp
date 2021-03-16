#include "Hooks.h"

#include "HorseMeterManager.h"

namespace Hooks
{
	void Install()
	{
		HorseMeterManager::InstallHooks();
		logger::info("Installed all hooks");
	}
}