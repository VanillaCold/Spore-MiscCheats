#include "stdafx.h"
#include "SetGameMode.h"

SetGameMode::SetGameMode()
{
}


SetGameMode::~SetGameMode()
{
}


void SetGameMode::ParseLine(const ArgScript::Line& line)
{
	auto arg1 = line.GetOption("name", 1);
	auto arg2 = line.GetOption("id", 1);
	if (arg1)
	{
		GameModeManager.SetActiveModeByName(arg1[0]);
		return;
	}
	if (arg2)
	{
		GameModeManager.SetActiveMode(mpFormatParser->ParseUInt(arg2[0]));
	}
}

const char* SetGameMode::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "This cheat does something.";
	}
	else {
		return "SetGameMode: Elaborate description of what this cheat does.";
	}
}
