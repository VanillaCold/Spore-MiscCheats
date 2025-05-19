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
		return "Sets the current active game-mode.";
	}
	else {
		string str = "SetGameMode: Sets the active game-mode depending on the mode ID (or name) inputted.";
		str += "Usage: setGameMode [-name/-id] [gameModeName/gameModeID]";
		return str.c_str();
	}
}
